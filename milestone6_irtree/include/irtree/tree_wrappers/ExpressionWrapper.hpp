//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//


#pragma once

#include "irtree/tree_wrappers/SubtreeWrapper.hpp"
#include "irtree/nodes/statements/Statement.hpp"


namespace IRT {

class ExpressionWrapper: public SubtreeWrapper,
 public std::enable_shared_from_this<ExpressionWrapper> {
 public:
  explicit ExpressionWrapper(std::shared_ptr<Expression> expression);

  std::shared_ptr<Expression> ToExpression() override;
  std::shared_ptr<Statement> ToStatement() override;
  std::shared_ptr<Statement> ToConditional(
      Label true_label, Label false_label) override;

  virtual ~ExpressionWrapper() = default;

 private:
  std::shared_ptr<Expression> expression_;
};

}

