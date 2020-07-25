//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/ExpressionList.hpp"


namespace IRT {

void ExpressionList::AddItem(std::shared_ptr<Expression> expression) {
  expressions.push_back(expression);
}

void ExpressionList::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
