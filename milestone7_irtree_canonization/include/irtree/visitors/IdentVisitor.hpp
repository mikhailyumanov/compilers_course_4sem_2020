#pragma once

#include "irtree/visitors/TemplateVisitor.hpp"
#include "irtree/visitors/BaseElements.hpp"
#include "irtree/nodes/expressions/EseqExpression.hpp"


namespace IRT {

enum class NodeType {
  ExpStatement = 1,
  JumpConditionalStatement,
  MoveStatement,
  SeqStatement,
  LabelStatement,
  JumpStatement,
  ConstExpression,
  BinopExpression,
  TempExpression,
  MemExpression,
  CallExpression,
  NameExpression,
  EseqExpression,
  ExpressionList
};

class IdentVisitor: public TemplateVisitor<NodeType>,
  public std::enable_shared_from_this<IdentVisitor> {

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

  NodeType Accept(std::shared_ptr<BaseElement> element) override;
};

}
