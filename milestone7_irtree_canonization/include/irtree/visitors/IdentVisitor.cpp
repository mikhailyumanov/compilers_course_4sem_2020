#include "irtree/visitors/IdentVisitor.hpp"


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

}
