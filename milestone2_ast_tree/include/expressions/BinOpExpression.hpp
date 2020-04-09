#pragma once
#include "Expression.hpp"

struct BinOpExpression : Expression {
 public:
  BinOpExpression(Expression* lhs, int op, Expression* rhs)
  : lhs_{lhs}, op_{op}, rhs_{rhs} {}

  int eval() {
    return 0;
  }

 private:
  Expression* lhs_;
  Expression* rhs_;
  int op_;
};
