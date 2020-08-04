//
// Created by akhtyamovpavel on 4/15/20.
//

#pragma once

#include "irtree/nodes/expressions/Expression.hpp"
#include "irtree/nodes/statements/Statement.hpp"


namespace IRT {

struct IrtStorage {
  std::shared_ptr<Expression> expr = nullptr;
  std::shared_ptr<Statement> stmt = nullptr;
  std::shared_ptr<ExpressionList> expr_list = nullptr;
};

}
