#pragma once

#include "irtree/visitors/TemplateVisitor.hpp"
#include "irtree/visitors/IdentVisitor.hpp"
#include "irtree/visitors/VisitorStruct.hpp"


namespace IRT {

class DoubleCallEliminationVisitor: public TemplateVisitor<IRT::IrtStorage>,
 public std::enable_shared_from_this<DoubleCallEliminationVisitor> {

 public:
  DoubleCallEliminationVisitor();

  void Visit(std::shared_ptr<ExpStatement> element) override;
  void Visit(std::shared_ptr<JumpConditionalStatement> element) override;
  void Visit(std::shared_ptr<MoveStatement> element) override;
  void Visit(std::shared_ptr<SeqStatement> element) override;
  void Visit(std::shared_ptr<LabelStatement> element) override;
  void Visit(std::shared_ptr<JumpStatement> element) override;
  void Visit(std::shared_ptr<ReturnStatement> element) override;

  void Visit(std::shared_ptr<ConstExpression> element) override;
  void Visit(std::shared_ptr<BinopExpression> element) override;
  void Visit(std::shared_ptr<TempExpression> element) override;
  void Visit(std::shared_ptr<MemExpression> element) override;
  void Visit(std::shared_ptr<CallExpression> element) override;
  void Visit(std::shared_ptr<NameExpression> element) override;
  void Visit(std::shared_ptr<EseqExpression> element) override;

  void Visit(std::shared_ptr<ExpressionList> element) override;

  IRT::IrtStorage Accept(std::shared_ptr<BaseElement> element) override;
};

}

