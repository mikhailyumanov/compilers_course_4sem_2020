//
// Created by akhtyamovpavel on 4/10/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/expressions/TempExpression.hpp"


IRT::TempExpression::TempExpression(const IRT::Temporary& temporary)
  : temp(temporary) {
}

void IRT::TempExpression::Accept(std::shared_ptr<IRT::Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
