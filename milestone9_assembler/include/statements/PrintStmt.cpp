#include "statements/PrintStmt.hpp"


PrintStmt::PrintStmt(std::shared_ptr<Expression> expr) : expr{expr} {
}

void PrintStmt::Perform() const {
  std::cout << "Print: " << expr->Eval();
}

void PrintStmt::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
