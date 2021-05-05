//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/expressions/CallExpression.hpp"
void IRT::CallExpression::Accept(std::shared_ptr<IRT::Visitor> visitor) {
  visitor->Visit(shared_from_this());

}
IRT::CallExpression::CallExpression(
    std::shared_ptr<IRT::Expression> expression,
    std::shared_ptr<IRT::ExpressionList> args)
  : function_name(expression), args(args) {

}
