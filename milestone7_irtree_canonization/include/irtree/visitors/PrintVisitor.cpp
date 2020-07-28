//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/visitors/PrintVisitor.hpp"
#include "irtree/visitors/BaseElements.hpp"
#include "irtree/nodes/expressions/EseqExpression.hpp"

#define PRINT_DOWN ++num_tabs_;
#define PRINT_UP --num_tabs_;


namespace IRT {

PrintVisitor::PrintVisitor(const std::string& filename): stream_(filename) {
}

void PrintVisitor::Visit(std::shared_ptr<ExpStatement> element) {
  PrintTabs();
  stream_ << "ExpStatement:" << std::endl;

  PRINT_DOWN
  element->GetExpression()->Accept(shared_from_this());
  PRINT_UP
}

void PrintVisitor::Visit(std::shared_ptr<JumpConditionalStatement> element) {
  PrintTabs();
  stream_ << "JumpConditionalStatement: "
          << ToString(element->operator_type) << std::endl;

  PrintTabs();
  stream_ << "TrueLabel: "
          << element->label_true.ToString() << std::endl;

  PrintTabs();
  stream_ << "FalseLabel: "
          << element->label_false.ToString() << std::endl;

  PRINT_DOWN
  element->lhs->Accept(shared_from_this());
  element->rhs->Accept(shared_from_this());
  PRINT_UP
}

void PrintVisitor::Visit(std::shared_ptr<MoveStatement> element) {
  PrintTabs();
  stream_ << "MoveStatement:" << std::endl;

  PRINT_DOWN
  element->target->Accept(shared_from_this());
  element->source->Accept(shared_from_this());
  PRINT_UP
}

void PrintVisitor::Visit(std::shared_ptr<SeqStatement> element) {
  PrintTabs();
  stream_ << "SeqStatement:" << std::endl;

  PRINT_DOWN
  element->lhs->Accept(shared_from_this());
  element->rhs->Accept(shared_from_this());
  PRINT_UP
}

void PrintVisitor::Visit(std::shared_ptr<LabelStatement> element) {
  PrintTabs();
  stream_ << "LabelStatement: " 
          << element->label.ToString() << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<JumpStatement> element) {
  PrintTabs();
  stream_ << "JumpStatement: "
          << element->label.ToString() << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<ConstExpression> element) {
  PrintTabs();
  stream_ << "ConstExpression " << element->GetValue() << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<BinopExpression> element) {
  PrintTabs();
  stream_ << "BinopExpression: "
          << ToString(element->operator_type) << std::endl;

  PRINT_DOWN
  element->lhs->Accept(shared_from_this());
  element->rhs->Accept(shared_from_this());
  PRINT_UP
}

void PrintVisitor::Visit(std::shared_ptr<TempExpression> element) {
  PrintTabs();
  stream_ << "TempExpression: "
          << element->temp.ToString() << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<MemExpression> element) {
  PrintTabs();
  stream_ << "MemExpression: " << std::endl;

  PRINT_DOWN
  element->expr->Accept(shared_from_this());
  PRINT_UP
}

void PrintVisitor::Visit(std::shared_ptr<CallExpression> element) {
  PrintTabs();
  stream_ << "CallExpression: " << std::endl;

  PRINT_DOWN
  element->function_name->Accept(shared_from_this());
  element->args->Accept(shared_from_this());
  PRINT_UP
}

void PrintVisitor::Visit(std::shared_ptr<ExpressionList> element) {
  PrintTabs();
  stream_ << "ExpressionList: " << std::endl;

  PRINT_DOWN
  for (auto&& expr: element->expr_list) {
    expr->Accept(shared_from_this());
  }
  PRINT_UP
}

void PrintVisitor::Visit(std::shared_ptr<NameExpression> element) {
  PrintTabs();
  stream_ << "NameExpression: "
          << element->label.ToString() << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<EseqExpression> element) {
  PrintTabs();
  stream_ << "EseqExpression:" << std::endl;
  PRINT_DOWN
  element->stmt->Accept(shared_from_this());
  element->expr->Accept(shared_from_this());
  PRINT_UP

}

void PrintVisitor::PrintTabs() {
  for (int i = 0; i < num_tabs_; (stream_ << '\t', ++i));
}

PrintVisitor::~PrintVisitor() {
  stream_.close();
}

}
