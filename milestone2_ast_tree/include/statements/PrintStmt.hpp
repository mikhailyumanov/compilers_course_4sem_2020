#pragma once

#include "expressions/Expression.hpp"
#include "statements/Statement.hpp"


class PrintStmt: Statement {
 public:
  PrintStmt(std::shared_ptr<Expression> expr);

  void Perform() const override;

 private:
  std::shared_ptr<Expression> expr_;

};
