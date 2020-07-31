#pragma once

#include "irtree/blocks/Block.hpp"


namespace IRT {

class Trace: public std::enable_shared_from_this<Trace> {
 public:
  Trace(std::vector<std::shared_ptr<Block>> trace);
  void PrintTrace(const std::string& filename) const;

 private:
  std::vector<std::shared_ptr<Block>> trace_;
};

}
