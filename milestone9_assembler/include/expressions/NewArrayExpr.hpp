#pragma once

#include "Expression.hpp"

class NewArrayExpr: public Expression, 
  public std::enable_shared_from_this<NewArrayExpr> {
 public:
  NewArrayExpr(const std::string& type, std::shared_ptr<Expression> expr);

  int Eval() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::string type;
  std::shared_ptr<Expression> expr;
};
