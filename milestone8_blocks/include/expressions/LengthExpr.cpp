#include "expressions/LengthExpr.hpp"

LengthExpr::LengthExpr(std::shared_ptr<Expression> expr)
  : expr{expr} {
}

int LengthExpr::Eval() const {
  return 0;
}

void LengthExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
