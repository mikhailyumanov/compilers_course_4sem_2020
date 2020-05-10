#include "expressions/NewExpr.hpp"

NewExpr::NewExpr(const std::string& type) : type_{type} {
}

int NewExpr::Eval() const {
  return 0;
}
