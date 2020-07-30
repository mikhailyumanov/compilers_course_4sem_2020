#include "irtree/blocks/BlockTree.hpp"

#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <queue>


namespace IRT {

BlockTree::BlockTree(std::shared_ptr<Statement> pre_root)
  : ident_visitor_{std::make_shared<IdentVisitor>()} {
  assert(pre_root != nullptr);
  CanonizeIrtree(pre_root);

  std::shared_ptr<SeqStatement> root;
  if (GetType(pre_root) != NodeType::SeqStatement) {
    root = std::make_shared<SeqStatement>(
        std::make_shared<LabelStatement>(Label()),
        pre_root);
  } else {
    root = GetSeqStmt(pre_root);
  }

  //check if first stmt is Label
  if (GetType(GetStmt(root)) != NodeType::LabelStatement) {
    root = std::make_shared<SeqStatement>(
        std::make_shared<LabelStatement>(Label()),
        root);
  }

  //close last block
  auto it = root;
  for (; GetType(it->rhs) == NodeType::SeqStatement; it = GetNextSeq(it));
  auto tmp = it->rhs;
  it->rhs = std::make_shared<SeqStatement>(
      tmp, 
      std::make_shared<SeqStatement>(
        std::make_shared<JumpStatement>(Label("%done")),
        std::make_shared<SeqStatement>(
          std::make_shared<LabelStatement>(Label("%done")),
          std::make_shared<LabelStatement>(Label()))));

  //set jumps
  it = root;
  for (; GetType(it->rhs) == NodeType::SeqStatement; it = GetNextSeq(it)) {
    if (GetType(GetStmt(GetNextSeq(it))) == NodeType::LabelStatement &&
        GetType(GetStmt(it)) != NodeType::JumpStatement &&
        GetType(GetStmt(it)) != NodeType::JumpConditionalStatement) {
      SetJump(GetNextSeq(it), GetLabelStmt(GetStmt(GetNextSeq(it)))->label);
    }
  }

  //irtree -> block tree
// DEBUG root_ = std::make_shared<Block>(root, std::shared_ptr<SeqStatement>());
  BuildBlocks(root);
}

void BlockTree::PrintTree(const std::string& filename) const {
  DEBUG_SINGLE("BlockTree::PrintTree")

  static auto print_visitor = std::make_shared<PrintVisitor>(filename);
  root_->GetLabelSeq()->Accept(print_visitor);

  std::ofstream stream(filename + "_blocks");
  Routine routine = [&stream](std::shared_ptr<Block> it) {
    stream << "Current: " << it->GetLabelName() << std::endl;
    stream << "Prev: " << std::endl << " > ";
    for (auto&& prev : it->GetPrev()) {
      stream << prev->GetLabelName() << ", ";
    }
    stream << std::endl << "Next: " << std::endl << " > ";
    for (auto&& next : it->GetNext()) {
      stream << next->GetLabelName() << ", ";
    }
    stream << std::endl << std::endl;
  };

  BFS(routine);

  DEBUG_SINGLE("BFS finished")

  stream.close();
}

void BlockTree::BFS(Routine routine) const {
  std::unordered_set<std::string> visited;
  std::queue<std::shared_ptr<Block>> nodes;
  nodes.push(root_);
  while (!nodes.empty()) {
    DEBUG_SINGLE("BFS")
    auto it = nodes.front();
    visited.insert(it->GetLabelName());

    routine(it);

    for (auto&& child : it->GetNext()) {
      if (visited.find(child->GetLabelName()) == visited.end()) {
        nodes.push(child);
      }
    }
    nodes.pop();
  }
}

void BlockTree::CanonizeIrtree(std::shared_ptr<Statement>& root) const {
  root = std::make_shared<DoubleCallEliminationVisitor>()->Accept(root).stmt;
  root = std::make_shared<EseqEliminationVisitor>()->Accept(root).stmt;
  root = std::make_shared<LinearizeVisitor>()->Accept(root).stmt;
}

void BlockTree::BuildBlocks(std::shared_ptr<SeqStatement> root) {
  std::unordered_map<std::string, std::shared_ptr<Block>> block_mapping;

  // make blocks
  auto it = root;
  std::shared_ptr<SeqStatement> current_label = root;
  for (; GetType(it->rhs) == NodeType::SeqStatement; it = GetNextSeq(it)) {
    NodeType type = GetType(GetStmt(it));
    if (type == NodeType::LabelStatement) {
      current_label = it;
    } else if (type == NodeType::JumpStatement ||
               type == NodeType::JumpConditionalStatement) {
      block_mapping[GetLabelStmt(GetStmt(current_label))->label.ToString()] = 
        std::make_shared<Block>(current_label, it);
    }
    DEBUG_SINGLE((GetType(GetSeqStmt(it->rhs)->rhs) == NodeType::SeqStatement))
  }

  // make 'done' block
  block_mapping["%done"] = std::make_shared<Block>(
      it, // 'it' points to SeqStmt-parent of 'done' label now.
      std::make_shared<SeqStatement>(
        std::make_shared<JumpStatement>(Label()),
        std::make_shared<LabelStatement>(Label())));

  // set root_
  root_ = block_mapping[GetLabelStmt(GetStmt(root))->label.ToString()];

  // bind blocks together
  for (auto&& pair : block_mapping) {
    if (pair.first == "%done") {
      continue;
    }

    DEBUG_SINGLE("build blocks: " + pair.first)
    DEBUG_SINGLE("build blocks: " << (bool) pair.second)

    auto parent = pair.second;
    if (GetType(GetStmt(parent->GetJumpSeq())) == NodeType::JumpStatement) {
      auto child = block_mapping[GetJumpStmt(
          GetStmt(parent->GetJumpSeq()))->label.ToString()];
      parent->AddNext(child);
      child->AddPrev(parent);

    } else if (GetType(GetStmt(parent->GetJumpSeq())) == 
        NodeType::JumpConditionalStatement) {
      auto jump = GetCJumpStmt(GetStmt(parent->GetJumpSeq()));
      auto true_child = block_mapping[jump->label_true.ToString()];
      auto false_child = block_mapping[jump->label_false.ToString()];
      parent->AddNext(false_child); // false lablel first
      parent->AddNext(true_child);
      true_child->AddPrev(parent);
      false_child->AddPrev(parent);
    }
  }
}

std::shared_ptr<Statement> BlockTree::GetStmt(
      std::shared_ptr<SeqStatement> element) const {
  return element->lhs;
}

std::shared_ptr<SeqStatement> BlockTree::GetNextSeq(
    std::shared_ptr<SeqStatement> element) {
  return GetSeqStmt(element->rhs);
}

void BlockTree::SetJump(std::shared_ptr<SeqStatement> element, Label label) {
  auto tmp = GetStmt(element);
  element->lhs = std::make_shared<JumpStatement>(label);
  element->rhs = std::make_shared<SeqStatement>(tmp, element->rhs);
}

NodeType BlockTree::GetType(std::shared_ptr<Statement> stmt) {
  return ident_visitor_->Accept(stmt);
}

std::shared_ptr<SeqStatement> BlockTree::GetSeqStmt(
    std::shared_ptr<Statement> stmt) {
  assert(GetType(stmt) == NodeType::SeqStatement);
  return std::dynamic_pointer_cast<SeqStatement>(stmt);
}

std::shared_ptr<LabelStatement> BlockTree::GetLabelStmt(
    std::shared_ptr<Statement> stmt) {
  assert(GetType(stmt) == NodeType::LabelStatement);
  return std::dynamic_pointer_cast<LabelStatement>(stmt);
}

std::shared_ptr<JumpStatement> BlockTree::GetJumpStmt(
    std::shared_ptr<Statement> stmt) {
  assert(GetType(stmt) == NodeType::JumpStatement);
  return std::dynamic_pointer_cast<JumpStatement>(stmt);
}

std::shared_ptr<JumpConditionalStatement> BlockTree::GetCJumpStmt(
    std::shared_ptr<Statement> stmt) {
  assert(GetType(stmt) == NodeType::JumpConditionalStatement);
  return std::dynamic_pointer_cast<JumpConditionalStatement>(stmt);
}

}
