//
// Created by akhtyamovpavel on 4/15/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/expressions/EseqExpression.hpp"


namespace IRT {

EseqExpression::EseqExpression(std::shared_ptr<Statement> statement,
    std::shared_ptr<Expression> expression)
  : statement(statement), expression(expression) {
}

void EseqExpression::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
