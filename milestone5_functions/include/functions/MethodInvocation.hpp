#pragma once

#include "expressions/Expression.hpp"
#include "functions/CommaExprList.hpp"
#include "scopes/Symbol.hpp"


class MethodInvocation: 
  public std::enable_shared_from_this<MethodInvocation> {
 public:
  MethodInvocation(std::shared_ptr<Expression> expr, const Symbol& name,
      std::shared_ptr<CommaExprList> comma_expr_list);

  std::shared_ptr<Expression> expr;
  Symbol name;
  std::shared_ptr<CommaExprList> comma_expr_list;
};