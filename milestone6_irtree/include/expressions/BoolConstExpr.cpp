#include "expressions/BoolConstExpr.hpp"

int TrueExpr::Eval() const {
  return true;
}

void TrueExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

int FalseExpr::Eval() const {
  return false;
}

void FalseExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

