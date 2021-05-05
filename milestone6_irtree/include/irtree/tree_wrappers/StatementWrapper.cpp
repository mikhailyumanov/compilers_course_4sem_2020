//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include <cassert>

#include "irtree/tree_wrappers/StatementWrapper.hpp"


namespace IRT {

StatementWrapper::StatementWrapper(std::shared_ptr<Statement> statement)
  : statement_(statement) {
}

std::shared_ptr<Expression> StatementWrapper::ToExpression() {
  assert(false);
}

std::shared_ptr<Statement> StatementWrapper::ToStatement() {
  return statement_;
}

std::shared_ptr<Statement> StatementWrapper::ToConditional(
    Label true_label, Label false_label) {
  assert(false);
}

}
