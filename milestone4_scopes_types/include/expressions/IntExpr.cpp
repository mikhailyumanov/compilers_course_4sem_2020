#include "expressions/IntExpr.hpp"


IntExpr::IntExpr(int value) : value{value} {
}

int IntExpr::Eval() const {
  return value;
}

void IntExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
