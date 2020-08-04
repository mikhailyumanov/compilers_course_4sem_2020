//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/tree_wrappers/conditional_wrappers/ConditionalWrapper.hpp"
#include "irtree/types/LogicOperatorType.hpp"


namespace IRT {

class RelativeConditionalWrapper: public ConditionalWrapper,
  public std::enable_shared_from_this<RelativeConditionalWrapper> {
 public:
  RelativeConditionalWrapper(LogicOperatorType type, 
      std::shared_ptr<Expression> lhs, 
      std::shared_ptr<Expression> rhs);
  std::shared_ptr<Statement> ToConditional(
      Label true_label, Label false_label) override;

 public:
  LogicOperatorType operator_type;
  std::shared_ptr<Expression> lhs;
  std::shared_ptr<Expression> rhs;
};

}


