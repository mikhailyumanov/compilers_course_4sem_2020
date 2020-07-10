#include "expressions/NewArrayExpr.hpp"


NewArrayExpr::NewArrayExpr(
    const std::string& type, std::shared_ptr<Expression> expr)
  : type{type}, expr{expr} {
}

int NewArrayExpr::Eval() const {
  return 0;
}

void NewArrayExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
