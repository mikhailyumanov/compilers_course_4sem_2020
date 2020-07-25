//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/tree_wrappers/conditional_wrappers/AndConditionalWrapper.hpp"
#include "irtree/nodes/statements/SeqStatement.hpp"
#include "irtree/nodes/statements/LabelStatement.hpp"


namespace IRT {

AndConditionalWrapper::AndConditionalWrapper(
    std::shared_ptr<SubtreeWrapper> lhs, 
    std::shared_ptr<SubtreeWrapper> rhs)
  : lhs_(lhs), rhs_(rhs) {
}

std::shared_ptr<Statement> AndConditionalWrapper::ToConditional(
    Label true_label, Label false_label) {
  Label middle_label;

  return std::make_shared<SeqStatement>(
    lhs_->ToConditional(middle_label, false_label),
    std::make_shared<SeqStatement>(
      std::make_shared<LabelStatement>(middle_label),
      rhs_->ToConditional(true_label, false_label))
  );
}

}
