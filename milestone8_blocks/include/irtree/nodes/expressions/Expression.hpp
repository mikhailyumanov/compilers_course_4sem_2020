#pragma once

#include "irtree/nodes/BaseElement.hpp"


namespace IRT {

class Expression: public BaseElement {
 public:
  virtual ~Expression() = default;
};

}
