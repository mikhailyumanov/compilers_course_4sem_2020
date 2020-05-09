#pragma once

#include <memory>

#include "expressions/Expression.hpp"


class TrueExpr: Expression {
 public:
  int Eval() const override;
}

class FalseExpr: Expression {
 public:
  int Eval() const override;
}
