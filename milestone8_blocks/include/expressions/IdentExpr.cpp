#include "expressions/IdentExpr.hpp"


IdentExpr::IdentExpr(const std::string& name) : name{name} {
}

void IdentExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

int IdentExpr::Eval() const {
  return 0;
}
