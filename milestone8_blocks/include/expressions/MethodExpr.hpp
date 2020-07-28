#pragma once

#include "Expression.hpp"
#include "functions/MethodInvocation.hpp"

class MethodExpr: public Expression, 
  public std::enable_shared_from_this<MethodExpr> {
 public:
  MethodExpr(std::shared_ptr<MethodInvocation> invocation);

  int Eval() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<MethodInvocation> invocation;
};
