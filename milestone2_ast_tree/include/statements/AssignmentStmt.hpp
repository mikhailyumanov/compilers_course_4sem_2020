#pragma once

#include "statements/Statement.hpp"
#include "value_categories/Lvalue.hpp"


class AssignmentStmt: public Statement,
  public std::enable_shared_from_this<AssignmentStmt> {
 public:
  AssignmentStmt(std::shared_ptr<Lvalue> lvalue,
      std::shared_ptr<Expression> expr);
  void Accept(std::shared_ptr<Visitor> visitor) override;
  void Perform() const override;

  std::shared_ptr<Lvalue> lvalue;
  std::shared_ptr<Expression> expr;
};
