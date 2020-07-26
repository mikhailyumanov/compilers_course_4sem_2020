#include "expressions/MethodExpr.hpp"

MethodExpr::MethodExpr(std::shared_ptr<MethodInvocation> invocation)
  : invocation{invocation} {
}

int MethodExpr::Eval() const {
  return 0;
}

void MethodExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
