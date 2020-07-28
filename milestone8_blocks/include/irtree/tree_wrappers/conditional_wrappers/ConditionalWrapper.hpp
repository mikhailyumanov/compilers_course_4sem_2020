//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/tree_wrappers/SubtreeWrapper.hpp"


namespace IRT {

class ConditionalWrapper: public SubtreeWrapper,
 public std::enable_shared_from_this<ConditionalWrapper> {
 public:
  std::shared_ptr<Expression>  ToExpression() override;
  std::shared_ptr<Statement> ToStatement() override;

  virtual ~ConditionalWrapper() = default;
};

}


