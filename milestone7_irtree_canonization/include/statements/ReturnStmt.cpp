#include "statements/ReturnStmt.hpp"


ReturnStmt::ReturnStmt(std::shared_ptr<Expression> expr) : expr{expr} {
}

void ReturnStmt::Perform() const {
  // do nothing
}

void ReturnStmt::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
