//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/statements/JumpConditionalStatement.hpp"


namespace IRT {

JumpConditionalStatement::JumpConditionalStatement(
    LogicOperatorType type,
    std::shared_ptr<Expression> left,
    std::shared_ptr<Expression> right,
    Label label_true,
    Label label_false)
  : operator_type(type),
    lhs(left),
    rhs(right),
    label_true(label_true),
    label_false(label_false) {
}

void JumpConditionalStatement::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
