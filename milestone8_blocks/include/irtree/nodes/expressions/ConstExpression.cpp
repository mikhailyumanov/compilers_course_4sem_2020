//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/expressions/ConstExpression.hpp"


void IRT::ConstExpression::Accept(std::shared_ptr<IRT::Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

IRT::ConstExpression::ConstExpression(int value): value_(value) {

}

int IRT::ConstExpression::GetValue() const {
  return value_;
}
