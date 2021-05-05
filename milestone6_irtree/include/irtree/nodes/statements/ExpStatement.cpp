//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/statements/ExpStatement.hpp"


namespace IRT {

ExpStatement::ExpStatement(std::shared_ptr<Expression> expression)
  : expression_(expression) {
}

std::shared_ptr<Expression> ExpStatement::GetExpression() {
  return expression_;
}

void ExpStatement::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
