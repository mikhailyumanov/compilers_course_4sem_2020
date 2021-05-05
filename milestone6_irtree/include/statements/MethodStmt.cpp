#include "statements/MethodStmt.hpp"


MethodStmt::MethodStmt(std::shared_ptr<MethodInvocation> invocation)
  : invocation{invocation} {
}

void MethodStmt::Perform() const {
  // do nothing
}

void MethodStmt::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
