//
// Created by akhtyamovpavel on 4/10/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/nodes/expressions/Expression.hpp"


namespace IRT {

class MemExpression : public Expression,
 public std::enable_shared_from_this<MemExpression> {
 public:
  MemExpression(std::shared_ptr<Expression> expression);

  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  std::shared_ptr<Expression> expression;
};

}

