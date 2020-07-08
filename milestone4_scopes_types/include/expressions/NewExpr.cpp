#include "expressions/NewExpr.hpp"

NewExpr::NewExpr(const std::string& type) : type{type} {
}

int NewExpr::Eval() const {
  return 0;
}

void NewExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
