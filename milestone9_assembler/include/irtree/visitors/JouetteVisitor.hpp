#pragma once

#include <list>

#include "irtree/visitors/TemplateVisitor.hpp"
#include "irtree/visitors/IdentVisitor.hpp"
#include "irtree/visitors/VisitorStruct.hpp"
#include "jouette/elements.hpp"

namespace IRT {


class JouetteVisitor:
  public TemplateVisitor<std::shared_ptr<Jouette::Register>>,
  public std::enable_shared_from_this<JouetteVisitor> {
 public:
  JouetteVisitor();

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

  std::shared_ptr<Jouette::Register> Accept(
      std::shared_ptr<BaseElement> element) override;

  const std::vector<std::shared_ptr<Jouette::Instruction>>&
    GetInstructions() const;

 private:
  std::vector<std::shared_ptr<Jouette::Instruction>> lst;
};

}

