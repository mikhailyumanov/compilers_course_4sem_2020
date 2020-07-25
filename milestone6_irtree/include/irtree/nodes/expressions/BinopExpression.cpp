//
// Created by akhtyamovpavel on 4/9/20.
// Modified by Mikahil Yumanov on 7/21/20
//

#include "irtree/nodes/expressions/BinopExpression.hpp"


namespace IRT {

BinopExpression::BinopExpression(
    BinaryOperatorType type,
    std::shared_ptr<Expression> lhs,
    std::shared_ptr<Expression> rhs
  ) : operator_type(type), lhs(lhs), rhs(rhs) {
}

void BinopExpression::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
