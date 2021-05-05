//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/tree_wrappers/conditional_wrappers/NegateConditionalWrapper.hpp"

namespace IRT {

NegateConditionalWrapper::NegateConditionalWrapper(
    std::shared_ptr<SubtreeWrapper> wrapper)
  : wrapper_(wrapper) {
}

std::shared_ptr<Statement> NegateConditionalWrapper::ToConditional(
    Label true_label, Label false_label) {
  return wrapper_->ToConditional(false_label, true_label);
}

}
