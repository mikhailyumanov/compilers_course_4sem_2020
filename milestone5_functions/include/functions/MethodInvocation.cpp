#include "functions/MethodInvocation.hpp"


MethodInvocation::MethodInvocation(
    std::shared_ptr<Expression> expr, const Symbol& name,
    std::shared_ptr<CommaExprList> comma_expr_list)
  : expr{expr}, name{name}, comma_expr_list{comma_expr_list} {
}
