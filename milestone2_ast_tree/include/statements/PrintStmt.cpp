#pragma once

#include <iostream>
#include <memory>

#include "expressions/Expression.hpp"
#include "statements/PrintStmt.hpp"


PrintStmt::PrintStmt(std::shared_ptr<Expression> expr)
  : expr_{expr} {
}

PrintStmt::Perform() {
  std::cout << expr.Eval();
}
