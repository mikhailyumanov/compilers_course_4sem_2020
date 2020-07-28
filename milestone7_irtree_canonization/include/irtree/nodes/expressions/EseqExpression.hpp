//
// Created by akhtyamovpavel on 4/15/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/nodes/statements/Statement.hpp"
#include "irtree/nodes/expressions/Expression.hpp"


namespace IRT {

class EseqExpression: public Expression,
 public std::enable_shared_from_this<EseqExpression> {
 public:
  EseqExpression(std::shared_ptr<Statement> statement,
      std::shared_ptr<Expression> expression);

  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  std::shared_ptr<Statement> stmt;
  std::shared_ptr<Expression> expr;
};

}


