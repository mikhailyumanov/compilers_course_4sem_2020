#pragma once

#include <iostream>

#include "expressions/Expression.hpp"
#include "statements/Statement.hpp"


class ReturnStmt: public Statement,
  public std::enable_shared_from_this<ReturnStmt> {
 public:
  ReturnStmt(std::shared_ptr<Expression> expr);

  void Perform() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Expression> expr;

};
