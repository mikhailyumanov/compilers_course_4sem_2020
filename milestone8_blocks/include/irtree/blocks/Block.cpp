#include "irtree/blocks/Block.hpp"


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

}
