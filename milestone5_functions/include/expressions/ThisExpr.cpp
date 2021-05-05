#include "expressions/ThisExpr.hpp"


int ThisExpr::Eval() const {
  return 0;
}

void ThisExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
