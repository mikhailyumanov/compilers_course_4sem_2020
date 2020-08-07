#pragma once

#include "irtree/nodes/BaseElement.hpp"
#include "irtree/visitors/IdentVisitor.hpp"


namespace Jouette {

class Rule {
 public:
  virtual bool IsSuitable(std::shared_ptr<IRT::BaseElement>) const = 0;

  virtual ~Rule() = default;
};

}
