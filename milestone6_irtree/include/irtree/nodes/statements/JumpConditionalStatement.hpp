//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/nodes/statements/Statement.hpp"
#include "irtree/nodes/expressions/Expression.hpp"
#include "irtree/types/LogicOperatorType.hpp"
#include "irtree/generators/Label.hpp"


namespace IRT {

class JumpConditionalStatement: public Statement,
 public std::enable_shared_from_this<JumpConditionalStatement> {
 public:
  JumpConditionalStatement(
      LogicOperatorType type,
      std::shared_ptr<Expression> left,
      std::shared_ptr<Expression> right,
      Label label_true,
      Label label_false
      );

  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  LogicOperatorType operator_type;
  Label label_true;
  Label label_false;
  std::shared_ptr<Expression> lhs;
  std::shared_ptr<Expression> rhs;
};

}


