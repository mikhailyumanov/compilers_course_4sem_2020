#include "visitors/PrintVisitor.hpp"
#include "utils/elements.hpp"


PrintVisitor::PrintVisitor(const std::string& filename) :stream_(filename) {
}

void PrintVisitor::Visit(std::shared_ptr<Program> program) {
  stream_ << "Program" << std::endl;

  ++num_tabs_;

  program->main_class->Accept(shared_from_this());
  program->class_decl_list->Accept(shared_from_this());

  --num_tabs_;
}

void PrintVisitor::Visit(std::shared_ptr<MainClass> main_class) {
  PrintTabs();
  stream_ << "MainClass" << std::endl;

  ++num_tabs_;
  main_class->stmt_list->Accept(shared_from_this());
  --num_tabs_;
}

void PrintVisitor::Visit(std::shared_ptr<PrintStmt> print_stmt) {
  PrintTabs();
  stream_ << "PrintStmt" << std::endl;

  ++num_tabs_;
  print_stmt->expr->Accept(shared_from_this());
  --num_tabs_;
}

void PrintVisitor::Visit(std::shared_ptr<BinOpExpr> bin_op_expr) {
  PrintTabs();
  stream_ << "BinOpExpr" << std::endl;

  ++num_tabs_;
  bin_op_expr->lhs->Accept(shared_from_this());
  PrintTabs(); stream_ << (int) bin_op_expr->op << std::endl;
  bin_op_expr->rhs->Accept(shared_from_this());
  --num_tabs_;
}

void PrintVisitor::Visit(std::shared_ptr<TrueExpr> true_expr) {
  PrintTabs();
  stream_ << "TrueExpr" << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<FalseExpr> false_expr) {
  PrintTabs();
  stream_ << "FalseExpr" << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<IntExpr> int_expr) {
  PrintTabs();
  stream_ << "IntExpr" << int_expr->value << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<NewExpr> new_expr) {
  PrintTabs();
  stream_ << "NewExpr" << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<NotExpr> not_expr) {
  PrintTabs();
  stream_ << "NotExpr" << std::endl;

  ++num_tabs_;
  not_expr->expr->Accept(shared_from_this());
  --num_tabs_;
}

PrintVisitor::~PrintVisitor() {
  stream_.close();
}

void PrintVisitor::PrintTabs() {
  for (size_t i = 0; i < num_tabs_; stream_ << '\t', ++i);
}
