#include "irtree/visitors/LinearizeVisitor.hpp"


namespace IRT {

LinearizeVisitor::LinearizeVisitor() {
}

void LinearizeVisitor::Visit(std::shared_ptr<ExpStatement> element) {
  auto expr = Accept(element->GetExpression()).expr;
  element->SetExpression(expr);

  tos_value_.stmt = element;
}

void LinearizeVisitor::Visit(
    std::shared_ptr<JumpConditionalStatement> element) {
  auto lhs = Accept(element->lhs).expr;
  auto rhs = Accept(element->rhs).expr;
  element->lhs = lhs;
  element->rhs = rhs;

  tos_value_.stmt = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<MoveStatement> element) {
  auto target = Accept(element->target).expr;
  auto source = Accept(element->source).expr;
  element->target = target;
  element->source = source;

  tos_value_.stmt = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<SeqStatement> element) {
  auto lhs = Accept(element->lhs).stmt;

  if (IRT::GetNodeType(lhs) == NodeType::SeqStatement) {
    auto seq_stmt = std::dynamic_pointer_cast<IRT::SeqStatement>(lhs);
    auto new_lhs = seq_stmt->lhs;
    auto new_rhs = std::make_shared<IRT::SeqStatement>(
        seq_stmt->rhs,
        element->rhs);

    lhs = new_lhs;
    element->rhs = new_rhs;
  }
  element->lhs = lhs;

  auto rhs = Accept(element->rhs).stmt;
  element->rhs = rhs;

  tos_value_.stmt = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<LabelStatement> element) {
  tos_value_.stmt = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<JumpStatement> element) {
  tos_value_.stmt = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<ReturnStatement> element) {
  tos_value_.stmt = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<ConstExpression> element) {
  tos_value_.expr = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<BinopExpression> element) {
  auto lhs = Accept(element->lhs).expr;
  auto rhs = Accept(element->rhs).expr;
  element->lhs = lhs;
  element->rhs = rhs;

  tos_value_.expr = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<TempExpression> element) {
  tos_value_.expr = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<MemExpression> element) {
  auto expr = Accept(element->expr).expr;
  element->expr = expr;

  tos_value_.expr = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<CallExpression> element) {
  element->function_name->Accept(shared_from_this());
  element->args->Accept(shared_from_this());

  tos_value_.expr = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<ExpressionList> element) {
  for (auto& expr: element->expr_list) {
    auto tmp = Accept(expr).expr;
    expr = tmp;
  }
}

void LinearizeVisitor::Visit(std::shared_ptr<NameExpression> element) {
  tos_value_.expr = element;
}

void LinearizeVisitor::Visit(std::shared_ptr<EseqExpression> element) {
  auto stmt = Accept(element->stmt).stmt;
  auto expr = Accept(element->expr).expr;
  element->stmt = stmt;
  element->expr = expr;

  tos_value_.expr = element;
}

IRT::IrtStorage LinearizeVisitor::Accept(
    std::shared_ptr<BaseElement> element) {
  element->Accept(shared_from_this());
  return tos_value_;
}

}
