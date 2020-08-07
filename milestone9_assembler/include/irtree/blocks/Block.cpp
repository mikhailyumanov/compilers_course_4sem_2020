#include "irtree/blocks/Block.hpp"
#include "irtree/blocks/NodeAdapter.hpp"
#include "irtree/visitors/JouetteVisitor.hpp"


namespace IRT {

Block::Block(std::shared_ptr<IRT::SeqStatement> label,
    std::shared_ptr<IRT::SeqStatement> jump)
  : label_{label}, jump_{jump} {
}

std::string Block::GetLabelName() const {
  return 
    std::dynamic_pointer_cast<LabelStatement>(label_->lhs)->label.ToString();
}

std::shared_ptr<IRT::SeqStatement> Block::GetLabelSeq() const {
  return label_;
}

std::shared_ptr<IRT::SeqStatement> Block::GetJumpSeq() const {
  return jump_;
}

void Block::AddPrev(std::shared_ptr<Block> prev) {
  prev_.push_back(prev);
}

void Block::AddNext(std::shared_ptr<Block> next) {
  next_.push_back(next);
}

std::vector<std::shared_ptr<Block>> Block::GetPrev() const {
  return prev_;
}

std::vector<std::shared_ptr<Block>> Block::GetNext() const {
  return next_;
}

void Block::PrintBlock(const std::string& filename, bool is_main) const {
  if (IsDoneLabel(NodeAdapter(label_).GetLabel())) {
    return;
  }

  auto jouette_visitor = std::make_shared<JouetteVisitor>();
  auto it = label_;
  for (; IsSeqStmt(it->rhs) && it != jump_; it = GetSeqStmt(it->rhs)) {
    it->lhs->Accept(jouette_visitor);
  }

  if (!is_main && IsJumpStmt(it->lhs) && 
      IsDoneLabel(GetJumpStmt(it->lhs)->label)) {
    std::make_shared<ReturnStatement>()->Accept(jouette_visitor);
  } else {
    it->lhs->Accept(jouette_visitor);
  }

  auto print_visitor = GetPrinter(filename);
  for (auto&& instruction : jouette_visitor->GetInstructions()) {
    instruction->Accept(print_visitor);
  }
}

std::shared_ptr<Jouette::PrintVisitor> Block::GetPrinter(
    const std::string& filename) const {
  static auto print_visitor = std::make_shared<Jouette::PrintVisitor>(filename);
  return print_visitor;
}

}
