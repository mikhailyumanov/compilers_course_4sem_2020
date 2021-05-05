#pragma once

#include <memory>
#include <string>

#include "expressions/Expression.hpp"


class NotExpr: public Expression,
  public std::enable_shared_from_this<NotExpr> {
 public:
  NotExpr(std::shared_ptr<Expression> expr);
  
  int Eval() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Expression> expr;
};
