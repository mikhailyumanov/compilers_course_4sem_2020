#pragma once

#include "irtree/elements.hpp"


namespace IRT {

class Block: public std::enable_shared_from_this<Block> {
 public:
  Block(std::shared_ptr<IRT::SeqStatement> label, 
      std::shared_ptr<IRT::SeqStatement> jump);

  std::shared_ptr<IRT::SeqStatement> GetLabelSeq() const;
  std::shared_ptr<IRT::SeqStatement> GetJumpSeq() const;
 
 private:
  std::shared_ptr<IRT::SeqStatement> label_;
  std::shared_ptr<IRT::SeqStatement> jump_;
};

}
