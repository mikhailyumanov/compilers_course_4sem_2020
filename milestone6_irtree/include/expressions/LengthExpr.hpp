#pragma once

#include "Expression.hpp"

class LengthExpr: public Expression, 
  public std::enable_shared_from_this<LengthExpr> {
 public:
  LengthExpr(std::shared_ptr<Expression> expr);

  int Eval() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Expression> expr;
};
