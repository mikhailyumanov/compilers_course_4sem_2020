#include "irtree/visitors/IdentVisitor.hpp"

#include <cassert>


namespace IRT {

void IdentVisitor::Visit(std::shared_ptr<ExpStatement> element) {
  tos_value_ = NodeType::ExpStatement;
}

void IdentVisitor::Visit(std::shared_ptr<JumpConditionalStatement> element) {
  tos_value_ = NodeType::JumpConditionalStatement;
}

void IdentVisitor::Visit(std::shared_ptr<MoveStatement> element) {
  tos_value_ = NodeType::MoveStatement;
}

void IdentVisitor::Visit(std::shared_ptr<SeqStatement> element) {
  tos_value_ = NodeType::SeqStatement;
}

void IdentVisitor::Visit(std::shared_ptr<LabelStatement> element) {
  tos_value_ = NodeType::LabelStatement;
}

void IdentVisitor::Visit(std::shared_ptr<JumpStatement> element) {
  tos_value_ = NodeType::JumpStatement;
}

void IdentVisitor::Visit(std::shared_ptr<ReturnStatement> element) {
  tos_value_ = NodeType::ReturnStatement;
}

void IdentVisitor::Visit(std::shared_ptr<ConstExpression> element) {
  tos_value_ = NodeType::ConstExpression;
}

void IdentVisitor::Visit(std::shared_ptr<BinopExpression> element) {
  tos_value_ = NodeType::BinopExpression;
}

void IdentVisitor::Visit(std::shared_ptr<TempExpression> element) {
  tos_value_ = NodeType::TempExpression;
}

void IdentVisitor::Visit(std::shared_ptr<MemExpression> element) {
  tos_value_ = NodeType::MemExpression;
}

void IdentVisitor::Visit(std::shared_ptr<CallExpression> element) {
  tos_value_ = NodeType::CallExpression;
}

void IdentVisitor::Visit(std::shared_ptr<ExpressionList> element) {
  tos_value_ = NodeType::ExpressionList;
}

void IdentVisitor::Visit(std::shared_ptr<NameExpression> element) {
  tos_value_ = NodeType::NameExpression;
}

void IdentVisitor::Visit(std::shared_ptr<EseqExpression> eseq_expression) {
  tos_value_ = NodeType::EseqExpression;
}

NodeType IdentVisitor::Accept(std::shared_ptr<BaseElement> element) {
  element->Accept(shared_from_this());
  return tos_value_;
}


////////////////// GET TYPE //////////////////

NodeType GetNodeType(std::shared_ptr<BaseElement> element) {
  static auto ident_visitor = std::make_shared<IdentVisitor>();
  return ident_visitor->Accept(element);
}


bool IsExpStmt(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::ExpStatement;
}

bool IsJumpStmt(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::JumpStatement;
}

bool IsCJumpStmt(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::JumpConditionalStatement;
}

bool IsMoveStmt(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::MoveStatement;
}

bool IsSeqStmt(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::SeqStatement;
}

bool IsLabelStmt(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::LabelStatement;
}

bool IsReturnStmt(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::ReturnStatement;
}

bool IsConstExpr(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::ConstExpression;
}

bool IsBinopExpr(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::BinopExpression;
}

bool IsTempExpr(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::TempExpression;
}

bool IsMemExpr(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::MemExpression;
}

bool IsCallExpr(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::CallExpression;
}

bool IsNameExpr(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::NameExpression;
}

bool IsEseqExpr(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::EseqExpression;
}

bool IsExprList(std::shared_ptr<BaseElement> element) {
  return GetNodeType(element) == NodeType::ExpressionList;
}

//////////////// GET ELEMENT ////////////////

std::shared_ptr<ExpStatement> GetExpStmt(std::shared_ptr<BaseElement> element) {
  assert(IsExpStmt(element));
  return std::dynamic_pointer_cast<ExpStatement>(element);
}

std::shared_ptr<JumpStatement> GetJumpStmt(std::shared_ptr<BaseElement> element) {
  assert(IsJumpStmt(element));
  return std::dynamic_pointer_cast<JumpStatement>(element);
}

std::shared_ptr<JumpConditionalStatement> GetCJumpStmt(std::shared_ptr<BaseElement> element) {
  assert(IsCJumpStmt(element));
  return std::dynamic_pointer_cast<JumpConditionalStatement>(element);
}

std::shared_ptr<MoveStatement> GetMoveStmt(std::shared_ptr<BaseElement> element) {
  assert(IsMoveStmt(element));
  return std::dynamic_pointer_cast<MoveStatement>(element);
}

std::shared_ptr<SeqStatement> GetSeqStmt(std::shared_ptr<BaseElement> element) {
  assert(IsSeqStmt(element));
  return std::dynamic_pointer_cast<SeqStatement>(element);
}

std::shared_ptr<LabelStatement> GetLabelStmt(std::shared_ptr<BaseElement> element) {
  assert(IsLabelStmt(element));
  return std::dynamic_pointer_cast<LabelStatement>(element);
}

std::shared_ptr<ReturnStatement> GetReturnStmt(std::shared_ptr<BaseElement> element) {
  assert(IsReturnStmt(element));
  return std::dynamic_pointer_cast<ReturnStatement>(element);
}

std::shared_ptr<ConstExpression> GetConstExpr(std::shared_ptr<BaseElement> element) {
  assert(IsConstExpr(element));
  return std::dynamic_pointer_cast<ConstExpression>(element);
}

std::shared_ptr<BinopExpression> GetBinopExpr(std::shared_ptr<BaseElement> element) {
  assert(IsBinopExpr(element));
  return std::dynamic_pointer_cast<BinopExpression>(element);
}

std::shared_ptr<TempExpression> GetTempExpr(std::shared_ptr<BaseElement> element) {
  assert(IsTempExpr(element));
  return std::dynamic_pointer_cast<TempExpression>(element);
}

std::shared_ptr<MemExpression> GetMemExpr(std::shared_ptr<BaseElement> element) {
  assert(IsMemExpr(element));
  return std::dynamic_pointer_cast<MemExpression>(element);
}

std::shared_ptr<CallExpression> GetCallExpr(std::shared_ptr<BaseElement> element) {
  assert(IsCallExpr(element));
  return std::dynamic_pointer_cast<CallExpression>(element);
}

std::shared_ptr<NameExpression> GetNameExpr(std::shared_ptr<BaseElement> element) {
  assert(IsNameExpr(element));
  return std::dynamic_pointer_cast<NameExpression>(element);
}

std::shared_ptr<EseqExpression> GetEseqExpr(std::shared_ptr<BaseElement> element) {
  assert(IsEseqExpr(element));
  return std::dynamic_pointer_cast<EseqExpression>(element);
}

std::shared_ptr<ExpressionList> GetExprList(std::shared_ptr<BaseElement> element) {
  assert(IsExprList(element));
  return std::dynamic_pointer_cast<ExpressionList>(element);
}

}

