#pragma once

#include "expressions/Expression.hpp"
#include "visitors/Visitor.hpp"

class IdentExpr: public Expression,
  public std::enable_shared_from_this<IdentExpr> {
 public:
  IdentExpr(const std::string& name);
  void Accept(std::shared_ptr<Visitor> visitor) override;  
  int Eval() const override;

  std::string name;
};
