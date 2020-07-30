#include "irtree/blocks/BlockTree.hpp"

#include <cassert>


namespace IRT {

BlockTree::BlockTree(std::shared_ptr<Statement> pre_root)
  : ident_visitor_{std::make_shared<IdentVisitor>()} {
  assert(pre_root != nullptr);
  assert(GetType(pre_root) == NodeType::SeqStatement);

  auto root = std::dynamic_pointer_cast<SeqStatement>(pre_root);

  CanonizeIrtree(root);

  //check if first stmt is Label
  if (GetType(GetStmt(root)) != NodeType::LabelStatement) {
    root = std::make_shared<SeqStatement>(
        std::make_shared<LabelStatement>(Label()),
        root);
  }

  DEBUG_SINGLE("BlockTree::BlockTree")

  //set jumps
  auto it = root;
  for (; GetType(it->rhs) == NodeType::SeqStatement; it = GetNextSeq(it)) {
    if (GetType(GetStmt(GetNextSeq(it))) == NodeType::LabelStatement &&
        GetType(GetStmt(it)) != NodeType::JumpStatement &&
        GetType(GetStmt(it)) != NodeType::JumpConditionalStatement) {
      SetJump(GetNextSeq(it), std::dynamic_pointer_cast<LabelStatement>(
            GetStmt(GetNextSeq(it)))->label);
    }
  }

  //close last block
  auto tmp = it->rhs;
  it->rhs = std::make_shared<SeqStatement>(
      tmp, 
      std::make_shared<SeqStatement>(
        std::make_shared<JumpStatement>(Label("%done")),
        nullptr));
  
  //irtree -> block tree
  BuildBlocks(root);
}

void BlockTree::PrintTree(const std::string& filename) const {
  auto print_visitor = std::make_shared<PrintVisitor>(filename);
  root_->GetLabelSeq()->Accept(print_visitor);
}

void BlockTree::CanonizeIrtree(std::shared_ptr<SeqStatement> root) const {
  root->Accept(std::make_shared<DoubleCallEliminationVisitor>());
  root->Accept(std::make_shared<EseqEliminationVisitor>());
  root->Accept(std::make_shared<LinearizeVisitor>());
}

void BlockTree::BuildBlocks(std::shared_ptr<SeqStatement> root) {
  root_ = std::make_shared<Block>(root, nullptr);
  //TODO
}

std::shared_ptr<Statement> BlockTree::GetStmt(
      std::shared_ptr<SeqStatement> element) const {
  return element->lhs;
}

std::shared_ptr<SeqStatement> BlockTree::GetNextSeq(
    std::shared_ptr<SeqStatement> element) const {
  return std::dynamic_pointer_cast<SeqStatement>(element->rhs);
}

void BlockTree::SetJump(std::shared_ptr<SeqStatement> element, Label label) {
  auto tmp = GetStmt(element);
  element->lhs = std::make_shared<JumpStatement>(label);
  element->rhs = std::make_shared<SeqStatement>(tmp, element->rhs);
}

NodeType BlockTree::GetType(std::shared_ptr<Statement> stmt) {
  return ident_visitor_->Accept(stmt);
}

}
