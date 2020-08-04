//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/nodes/statements/Statement.hpp"
#include "irtree/nodes/expressions/Expression.hpp"


namespace IRT {

class MoveStatement: public Statement,
 public std::enable_shared_from_this<MoveStatement> {
 public:
  MoveStatement(std::shared_ptr<Expression> target,
      std::shared_ptr<Expression> source);

  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  std::shared_ptr<Expression> source;
  std::shared_ptr<Expression> target;
};

};


