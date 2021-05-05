#pragma once

#include "irtree/generators/Label.hpp"
#include "irtree/nodes/expressions/Expression.hpp"
#include "irtree/nodes/statements/Statement.hpp"


namespace IRT {

class SubtreeWrapper: public std::enable_shared_from_this<SubtreeWrapper> {
 public:
  virtual ~SubtreeWrapper() = default;
  virtual std::shared_ptr<Expression> ToExpression() = 0;
  virtual std::shared_ptr<Statement> ToStatement() = 0;
  virtual std::shared_ptr<Statement> ToConditional(
      Label true_label, Label false_label) = 0;
};

}
