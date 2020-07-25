//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/nodes/expressions/Expression.hpp"


namespace IRT {

class CallExpression: public Expression,
 public std::enable_shared_from_this<CallExpression> {
 public:
  CallExpression(std::shared_ptr<Expression> expression,
      std::shared_ptr<ExpressionList> args);

  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  std::shared_ptr<Expression> function_name;
  std::shared_ptr<ExpressionList> args;

};

}

