#include "irtree/visitors/DoNothingVisitor.hpp"


namespace IRT {

void DoNothingVisitor::Visit(std::shared_ptr<ExpStatement> element) {
  element->GetExpression()->Accept(shared_from_this());
}

void DoNothingVisitor::Visit(std::shared_ptr<JumpConditionalStatement> element) {
  element->lhs->Accept(shared_from_this());
  element->rhs->Accept(shared_from_this());
}

void DoNothingVisitor::Visit(std::shared_ptr<MoveStatement> element) {
  element->source->Accept(shared_from_this());
  element->target->Accept(shared_from_this());
}

void DoNothingVisitor::Visit(std::shared_ptr<SeqStatement> element) {
  element->lhs->Accept(shared_from_this());
  element->rhs->Accept(shared_from_this());
}

void DoNothingVisitor::Visit(std::shared_ptr<LabelStatement> element) {
  // do nothing
}

void DoNothingVisitor::Visit(std::shared_ptr<JumpStatement> element) {
  // do nothing
}

void DoNothingVisitor::Visit(std::shared_ptr<ConstExpression> element) {
  // do nothing
}

void DoNothingVisitor::Visit(std::shared_ptr<BinopExpression> element) {
  element->lhs->Accept(shared_from_this());
  element->rhs->Accept(shared_from_this());
}

void DoNothingVisitor::Visit(std::shared_ptr<TempExpression> element) {
  // do nothing
}

void DoNothingVisitor::Visit(std::shared_ptr<MemExpression> element) {
  element->expression->Accept(shared_from_this());
}

void DoNothingVisitor::Visit(std::shared_ptr<CallExpression> element) {
  element->function_name->Accept(shared_from_this());
  element->args->Accept(shared_from_this());
}

void DoNothingVisitor::Visit(std::shared_ptr<ExpressionList> element) {
  for (auto&& expression: element->expressions) {
    expression->Accept(shared_from_this());
  }
}

void DoNothingVisitor::Visit(std::shared_ptr<NameExpression> element) {
  // do nothing
}

void DoNothingVisitor::Visit(std::shared_ptr<EseqExpression> eseq_expression) {
  eseq_expression->statement->Accept(shared_from_this());
  eseq_expression->expression->Accept(shared_from_this());
}

}
