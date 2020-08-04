//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/tree_wrappers/SubtreeWrapper.hpp"


namespace IRT {
class StatementWrapper: public SubtreeWrapper,
 public std::enable_shared_from_this<StatementWrapper> {
 public:
  explicit StatementWrapper(std::shared_ptr<Statement> statement);

  std::shared_ptr<Expression> ToExpression() override;
  std::shared_ptr<Statement> ToStatement() override;
  std::shared_ptr<Statement> ToConditional(
      Label true_label, Label false_label) override;

 private:
  std::shared_ptr<Statement> statement_;
};

}

