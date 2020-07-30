#pragma once

#include "irtree/blocks/Block.hpp"


namespace IRT {

class Trace: public std::enable_shared_from_this<Trace> {
 public:
  Trace(std::shared_ptr<Block> first, std::shared_ptr<Block> last);

  void PrintTrace(const std::string& filename) const;

 private:
  std::shared_ptr<Block> GetNext() const;

  std::shared_ptr<Block> first_;
  std::shared_ptr<Block> last_;
};

}
