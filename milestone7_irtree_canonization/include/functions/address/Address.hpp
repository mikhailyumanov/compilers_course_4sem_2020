#pragma once

#include "irtree/nodes/expressions/Expression.hpp"


namespace IRT {

class Address {
 public:
  virtual ~Address() = default;
  virtual std::shared_ptr<Expression> ToExpression() = 0;
};

}
