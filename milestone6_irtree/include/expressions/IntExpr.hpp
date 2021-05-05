#pragma once

#include <memory>
#include <string>

#include "expressions/Expression.hpp"


class IntExpr: public Expression,
  public std::enable_shared_from_this<IntExpr> { 
 public:
  IntExpr(int value);
  
  int Eval() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  int value;
};
