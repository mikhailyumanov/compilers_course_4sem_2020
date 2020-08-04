//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/tree_wrappers/conditional_wrappers/RelativeConditionalWrapper.hpp"
#include "irtree/nodes/statements/JumpConditionalStatement.hpp"


namespace IRT {

RelativeConditionalWrapper::RelativeConditionalWrapper(
    LogicOperatorType type, 
    std::shared_ptr<Expression> lhs, 
    std::shared_ptr<Expression> rhs)
  : operator_type(type), lhs(lhs), rhs(rhs)  {
}

std::shared_ptr<Statement> RelativeConditionalWrapper::ToConditional(
    Label true_label, Label false_label) {
  return std::make_shared<JumpConditionalStatement>(
      operator_type,
      lhs,
      rhs,
      true_label,
      false_label);
}

}
