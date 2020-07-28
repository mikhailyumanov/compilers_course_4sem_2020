//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/tree_wrappers/conditional_wrappers/ConditionalWrapper.hpp"
#include "irtree/generators/Temporary.hpp"
#include "irtree/nodes/expressions/TempExpression.hpp"
#include "irtree/nodes/expressions/ConstExpression.hpp"
#include "irtree/nodes/expressions/EseqExpression.hpp"
#include "irtree/nodes/statements/SeqStatement.hpp"
#include "irtree/nodes/statements/MoveStatement.hpp"
#include "irtree/nodes/statements/LabelStatement.hpp"


namespace IRT {

std::shared_ptr<Expression> IRT::ConditionalWrapper::ToExpression() {
  auto temp_expression = std::make_shared<TempExpression>(Temporary());
  Label label_true;
  Label label_false;

  return std::make_shared<EseqExpression>(
    std::make_shared<SeqStatement>(
      std::make_shared<MoveStatement>(temp_expression,
        std::make_shared<ConstExpression>(1)),

      std::make_shared<SeqStatement>(
        ToConditional(label_true, label_false),

        std::make_shared<SeqStatement>(
          std::make_shared<LabelStatement>(label_false),

          std::make_shared<SeqStatement>(
            std::make_shared<MoveStatement>(temp_expression, 
              std::make_shared<ConstExpression>(0)),

            std::make_shared<LabelStatement>(label_true)
    )))),

    temp_expression
  );
}

std::shared_ptr<Statement> IRT::ConditionalWrapper::ToStatement() {
  return nullptr;
}

}
