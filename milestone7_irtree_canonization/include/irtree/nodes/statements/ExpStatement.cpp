//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/statements/ExpStatement.hpp"


namespace IRT {

ExpStatement::ExpStatement(std::shared_ptr<Expression> expression)
  : expr_(expression) {
}

std::shared_ptr<Expression> ExpStatement::GetExpression() {
  return expr_;
}

void ExpStatement::SetExpression(std::shared_ptr<Expression> expr) {
  expr_ = expr;
}

void ExpStatement::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
