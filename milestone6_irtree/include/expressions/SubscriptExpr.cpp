#include "expressions/SubscriptExpr.hpp"

SubscriptExpr::SubscriptExpr(
    std::shared_ptr<Expression> expr, std::shared_ptr<Expression> idx)
  : expr{expr}, idx{idx} {
}

int SubscriptExpr::Eval() const {
  return 0;
}

void SubscriptExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
