#pragma once

#include <iostream>

#include "expressions/Expression.hpp"
#include "statements/Statement.hpp"
#include "functions/MethodInvocation.hpp"


class MethodStmt: public Statement,
  public std::enable_shared_from_this<MethodStmt> {
 public:
  MethodStmt(std::shared_ptr<MethodInvocation> invocation);

  void Perform() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<MethodInvocation> invocation;

};
