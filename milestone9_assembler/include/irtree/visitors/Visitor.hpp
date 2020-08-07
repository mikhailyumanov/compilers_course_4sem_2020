#pragma once

#include <memory>

#include "debug.h"
#include "irtree/forward_decl.hpp"


namespace IRT {

class Visitor {
 public:
  virtual ~Visitor() = default;

  virtual void Visit(std::shared_ptr<ExpStatement> element) = 0;
  virtual void Visit(std::shared_ptr<JumpConditionalStatement> element) = 0;
  virtual void Visit(std::shared_ptr<MoveStatement> element) = 0;
  virtual void Visit(std::shared_ptr<SeqStatement> element) = 0;
  virtual void Visit(std::shared_ptr<LabelStatement> element) = 0;
  virtual void Visit(std::shared_ptr<JumpStatement> element) = 0;
  virtual void Visit(std::shared_ptr<ReturnStatement> element) = 0;

  virtual void Visit(std::shared_ptr<ConstExpression> element) = 0;
  virtual void Visit(std::shared_ptr<BinopExpression> element) = 0;
  virtual void Visit(std::shared_ptr<TempExpression> element) = 0;
  virtual void Visit(std::shared_ptr<MemExpression> element) = 0;
  virtual void Visit(std::shared_ptr<CallExpression> element) = 0;
  virtual void Visit(std::shared_ptr<NameExpression> element) = 0;
  virtual void Visit(std::shared_ptr<EseqExpression> element) = 0;

  virtual void Visit(std::shared_ptr<ExpressionList> element) = 0;
};

}
