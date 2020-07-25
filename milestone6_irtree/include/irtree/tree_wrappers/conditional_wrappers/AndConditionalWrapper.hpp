//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/tree_wrappers/conditional_wrappers/ConditionalWrapper.hpp"


namespace IRT {

class AndConditionalWrapper: public ConditionalWrapper,
 public std::enable_shared_from_this<AndConditionalWrapper> {
 public:
  AndConditionalWrapper(std::shared_ptr<SubtreeWrapper> lhs,
      std::shared_ptr<SubtreeWrapper> rhs);

  std::shared_ptr<Statement> ToConditional(
      Label true_label, Label false_label) override;

 private:
  std::shared_ptr<SubtreeWrapper> lhs_;
  std::shared_ptr<SubtreeWrapper> rhs_;
};

}

