#include "irtree/blocks/Block.hpp"


namespace IRT {

Block::Block(std::shared_ptr<IRT::SeqStatement> label,
    std::shared_ptr<IRT::SeqStatement> jump)
  : label_{label}, jump_{jump} {
}

std::shared_ptr<IRT::SeqStatement> Block::GetLabelSeq() const {
  return label_;
}

std::shared_ptr<IRT::SeqStatement> Block::GetJumpSeq() const {
  return jump_;
}

}
