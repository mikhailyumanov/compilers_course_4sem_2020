#include "irtree/visitors/DoubleCallEliminationVisitor.hpp"


namespace IRT {

DoubleCallEliminationVisitor::DoubleCallEliminationVisitor()
  : ident_visitor_{std::make_shared<IdentVisitor>()} {

}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<ExpStatement> element) {
  auto expr = Accept(element->GetExpression()).expr;
  element->SetExpression(expr);

  tos_value_.stmt = element;
}

void DoubleCallEliminationVisitor::Visit(
    std::shared_ptr<JumpConditionalStatement> element) {
  auto lhs = Accept(element->lhs).expr;
  auto rhs = Accept(element->rhs).expr;
  element->lhs = lhs;
  element->rhs = rhs;

  tos_value_.stmt = element;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<MoveStatement> element) {
  auto target = Accept(element->target).expr;
  auto source = Accept(element->source).expr;
  element->target = target;
  element->source = source;

  tos_value_.stmt = element;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<SeqStatement> element) {
  auto lhs = Accept(element->lhs).stmt;
  auto rhs = Accept(element->rhs).stmt;
  element->lhs = lhs;
  element->rhs = rhs;

  tos_value_.stmt = element;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<LabelStatement> element) {
  tos_value_.stmt = element;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<JumpStatement> element) {
  tos_value_.stmt = element;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<ConstExpression> element) {
  tos_value_.expr = element;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<BinopExpression> element) {
  auto lhs = Accept(element->lhs).expr;
  auto rhs = Accept(element->rhs).expr;
  element->lhs = lhs;
  element->rhs = rhs;

  tos_value_.expr = element;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<TempExpression> element) {
  tos_value_.expr = element;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<MemExpression> element) {
  auto expr = Accept(element->expr).expr;
  element->expr = expr;

  tos_value_.expr = element;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<CallExpression> element) {
  element->function_name->Accept(shared_from_this());
  element->args->Accept(shared_from_this());

  Temporary t;
  std::shared_ptr<IRT::Expression> tmp = std::make_shared<EseqExpression>(
      std::make_shared<MoveStatement>(
        std::make_shared<TempExpression>(t),
        element),
      std::make_shared<TempExpression>(t)
  );

  tos_value_.expr = tmp;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<ExpressionList> element) {
  for (auto& expr: element->expr_list) {
    auto tmp = Accept(expr).expr;
    expr = tmp;
  }
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<NameExpression> element) {
  tos_value_.expr = element;
}

void DoubleCallEliminationVisitor::Visit(std::shared_ptr<EseqExpression> element) {
  auto stmt = Accept(element->stmt).stmt;
  auto expr = Accept(element->expr).expr;
  element->stmt = stmt;
  element->expr = expr;

  tos_value_.expr = element;
}

IRT::IrtStorage DoubleCallEliminationVisitor::Accept(
    std::shared_ptr<BaseElement> element) {
  element->Accept(shared_from_this());
  return tos_value_;
}

}
