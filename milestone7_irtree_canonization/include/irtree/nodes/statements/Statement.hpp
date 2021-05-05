#pragma once

#include "irtree/nodes/BaseElement.hpp"

namespace IRT {

class Statement: public BaseElement {
 public:
  virtual ~Statement() = default;
};

}
