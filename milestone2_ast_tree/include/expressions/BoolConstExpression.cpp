#include "expressions/BoolConstExpression.hpp"


int TrueExpr::Eval() const {
  return true;
}

int FalseExpr::Eval() const {
  return false;
}
