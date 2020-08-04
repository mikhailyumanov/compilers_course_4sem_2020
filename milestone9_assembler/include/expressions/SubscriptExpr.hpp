#pragma once

#include "Expression.hpp"

class SubscriptExpr: public Expression, 
  public std::enable_shared_from_this<SubscriptExpr> {
 public:
  SubscriptExpr(std::shared_ptr<Expression> expr, std::shared_ptr<Expression> idx);

  int Eval() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Expression> expr;
  std::shared_ptr<Expression> idx;
};
