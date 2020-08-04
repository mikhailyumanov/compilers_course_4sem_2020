//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/tree_wrappers/conditional_wrappers/OrConditionalWrapper.hpp"
#include "irtree/nodes/statements/LabelStatement.hpp"
#include "irtree/nodes/statements/SeqStatement.hpp"


namespace IRT {

OrConditionalWrapper::OrConditionalWrapper(
    std::shared_ptr<SubtreeWrapper> lhs, 
    std::shared_ptr<SubtreeWrapper> rhs)
  : lhs_(lhs), rhs_(rhs) {
}

std::shared_ptr<Statement> OrConditionalWrapper::ToConditional(
    Label true_label, Label false_label) {
  Label middle_label;

  return std::make_shared<SeqStatement>(
    lhs_->ToConditional(true_label, middle_label),
    std::make_shared<SeqStatement>(
      std::make_shared<LabelStatement>(middle_label),
      rhs_->ToConditional(true_label, false_label))
  );
}

}
