//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/nodes/statements/Statement.hpp"
#include "irtree/nodes/expressions/Expression.hpp"


namespace IRT {

class ExpStatement: public Statement,
 public std::enable_shared_from_this<ExpStatement> {
 public:
  explicit ExpStatement(std::shared_ptr<Expression> expression);

  std::shared_ptr<Expression> GetExpression();
  void SetExpression(std::shared_ptr<Expression> expr);
  void Accept(std::shared_ptr<Visitor> visitor) override;

  ~ExpStatement() override = default;

 private:
  std::shared_ptr<Expression> expr_;
};

}

