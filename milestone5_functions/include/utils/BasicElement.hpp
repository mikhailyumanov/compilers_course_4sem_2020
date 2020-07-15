#pragma once

#include <memory>

#include "visitors/Visitor.hpp"


class BasicElement{
 public:
  virtual void Accept(std::shared_ptr<Visitor> visitor) = 0;

  virtual ~BasicElement() = default;
};
