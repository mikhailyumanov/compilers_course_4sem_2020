#pragma once

#include <memory>

#include "irtree/visitors/Visitor.hpp"


namespace IRT {

class BaseElement {
 public:
  virtual void Accept(std::shared_ptr<Visitor> visitor) = 0;

  virtual ~BaseElement() = default;
};

}
