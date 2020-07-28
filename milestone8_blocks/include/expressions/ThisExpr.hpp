#pragma once

#include <memory>
#include <string>

#include "expressions/Expression.hpp"


class ThisExpr: public Expression,
  public std::enable_shared_from_this<ThisExpr> {
 public:
  ThisExpr() = default;
  
  int Eval() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;
};
