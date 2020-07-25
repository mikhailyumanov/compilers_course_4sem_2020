//
// Created by akhtyamovpavel on 4/9/20.
// Modified by Mikahil Yumanov on 7/21/20
//

#pragma once

#include "irtree/types/BinaryOperatorType.hpp"
#include "irtree/nodes/expressions/Expression.hpp"


namespace IRT {

class BinopExpression: public Expression,
 public std::enable_shared_from_this<BinopExpression> {
 public:
  BinopExpression(
      BinaryOperatorType type,
      std::shared_ptr<Expression> lhs,
      std::shared_ptr<Expression> rhs);

  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  BinaryOperatorType operator_type;
  std::shared_ptr<Expression> lhs;
  std::shared_ptr<Expression> rhs;
};

}


