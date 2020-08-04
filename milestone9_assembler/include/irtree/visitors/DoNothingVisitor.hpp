#pragma once

#include "irtree/visitors/TemplateVisitor.hpp"
#include "irtree/visitors/VisitorStruct.hpp"


namespace IRT {

class DoNothingVisitor: public TemplateVisitor<IRT::IrtStorage> {

 public:
  void Visit(std::shared_ptr<ExpStatement> element) override;
  void Visit(std::shared_ptr<JumpConditionalStatement> element) override;
  void Visit(std::shared_ptr<MoveStatement> element) override;
  void Visit(std::shared_ptr<SeqStatement> element) override;
  void Visit(std::shared_ptr<LabelStatement> element) override;
  void Visit(std::shared_ptr<JumpStatement> element) override;

  void Visit(std::shared_ptr<ConstExpression> element) override;
  void Visit(std::shared_ptr<BinopExpression> element) override;
  void Visit(std::shared_ptr<TempExpression> element) override;
  void Visit(std::shared_ptr<MemExpression> element) override;
  void Visit(std::shared_ptr<CallExpression> element) override;
  void Visit(std::shared_ptr<NameExpression> element) override;
  void Visit(std::shared_ptr<EseqExpression> element) override;

  void Visit(std::shared_ptr<ExpressionList> element) override;
};

}

