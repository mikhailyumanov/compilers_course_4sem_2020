//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/tree_wrappers/ExpressionWrapper.hpp"
#include "irtree/nodes/statements/ExpStatement.hpp"
#include "irtree/nodes/statements/JumpConditionalStatement.hpp"
#include "irtree/nodes/expressions/ConstExpression.hpp"


IRT::ExpressionWrapper::ExpressionWrapper(
    std::shared_ptr<IRT::Expression> expression)
  : expression_(expression) {
}

std::shared_ptr<IRT::Expression> IRT::ExpressionWrapper::ToExpression() {
  return expression_;
}

std::shared_ptr<IRT::Statement> IRT::ExpressionWrapper::ToStatement() {
  return std::make_shared<ExpStatement>(expression_);
}

std::shared_ptr<IRT::Statement> IRT::ExpressionWrapper::ToConditional(
    IRT::Label true_label, IRT::Label false_label) {
  return std::make_shared<JumpConditionalStatement>(
      LogicOperatorType::NE,
      expression_,
      std::make_shared<ConstExpression>(0),
      true_label,
      false_label);
}

