#pragma once

#include "irtree/visitors/TemplateVisitor.hpp"
#include "irtree/base_elements.hpp"


namespace IRT {

enum class NodeType {
  ExpStatement = 1,
  JumpConditionalStatement,
  MoveStatement,
  SeqStatement,
  LabelStatement,
  JumpStatement,
  ReturnStatement,
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
  void Visit(std::shared_ptr<ReturnStatement> element) override;

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


NodeType GetNodeType(std::shared_ptr<BaseElement>);

bool IsExpStmt(std::shared_ptr<BaseElement>);
bool IsJumpStmt(std::shared_ptr<BaseElement>);
bool IsCJumpStmt(std::shared_ptr<BaseElement>);
bool IsMoveStmt(std::shared_ptr<BaseElement>);
bool IsSeqStmt(std::shared_ptr<BaseElement>);
bool IsLabelStmt(std::shared_ptr<BaseElement>);
bool IsReturnStmt(std::shared_ptr<BaseElement>);

bool IsConstExpr(std::shared_ptr<BaseElement>);
bool IsBinopExpr(std::shared_ptr<BaseElement>);
bool IsTempExpr(std::shared_ptr<BaseElement>);
bool IsMemExpr(std::shared_ptr<BaseElement>);
bool IsCallExpr(std::shared_ptr<BaseElement>);
bool IsNameExpr(std::shared_ptr<BaseElement>);
bool IsEseqExpr(std::shared_ptr<BaseElement>);

bool IsExprList(std::shared_ptr<BaseElement>);


std::shared_ptr<ExpStatement> GetExpStmt(std::shared_ptr<BaseElement>);
std::shared_ptr<JumpStatement> GetJumpStmt(std::shared_ptr<BaseElement>);
std::shared_ptr<JumpConditionalStatement> GetCJumpStmt(std::shared_ptr<BaseElement>);
std::shared_ptr<MoveStatement> GetMoveStmt(std::shared_ptr<BaseElement>);
std::shared_ptr<SeqStatement> GetSeqStmt(std::shared_ptr<BaseElement>);
std::shared_ptr<LabelStatement> GetLabelStmt(std::shared_ptr<BaseElement>);
std::shared_ptr<ReturnStatement> GetReturnStmt(std::shared_ptr<BaseElement>);

std::shared_ptr<ConstExpression> GetConstExpr(std::shared_ptr<BaseElement>);
std::shared_ptr<BinopExpression> GetBinopExpr(std::shared_ptr<BaseElement>);
std::shared_ptr<TempExpression> GetTempExpr(std::shared_ptr<BaseElement>);
std::shared_ptr<MemExpression> GetMemExpr(std::shared_ptr<BaseElement>);
std::shared_ptr<CallExpression> GetCallExpr(std::shared_ptr<BaseElement>);
std::shared_ptr<NameExpression> GetNameExpr(std::shared_ptr<BaseElement>);
std::shared_ptr<EseqExpression> GetEseqExpr(std::shared_ptr<BaseElement>);

std::shared_ptr<ExpressionList> GetExprList(std::shared_ptr<BaseElement>);

}
