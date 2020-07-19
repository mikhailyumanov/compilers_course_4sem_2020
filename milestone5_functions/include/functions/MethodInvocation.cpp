#include "functions/MethodInvocation.hpp"


MethodInvocation::MethodInvocation(
    std::shared_ptr<Expression> expr, const std::string& func_name,
    std::shared_ptr<CommaExprList> comma_expr_list)
  : expr{expr}, func_name{func_name}, comma_expr_list{comma_expr_list} {
}

void MethodInvocation::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
