#pragma once

#include "expressions/Expression.hpp"

class TrueExpr: public Expression,
  public std::enable_shared_from_this<TrueExpr> {
 public:
  int Eval() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;
};

class FalseExpr: public Expression,
  public std::enable_shared_from_this<FalseExpr> {
 public:
  int Eval() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;
};
