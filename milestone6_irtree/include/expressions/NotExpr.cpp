#include "expressions/NotExpr.hpp"


NotExpr::NotExpr(std::shared_ptr<Expression> expr)
  : expr{expr} {
}

int NotExpr::Eval() const {
  return !expr->Eval();
}

void NotExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
