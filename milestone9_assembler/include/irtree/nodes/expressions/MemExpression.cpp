//
// Created by akhtyamovpavel on 4/10/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/expressions/MemExpression.hpp"

namespace IRT {

MemExpression::MemExpression(std::shared_ptr<Expression> expression)
  : expr(expression) {
}

void MemExpression::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
