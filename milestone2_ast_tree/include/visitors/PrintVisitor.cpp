#include "visitors/PrintVisitor.hpp"


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

void PrintVisitor::Visit(std::shared_ptr<AssertStmt> assert_stmt) {
  PrintTabs();
  stream_ << "AssertStmt" << std::endl;

  ++num_tabs_;
  assert_stmt->expr->Accept(shared_from_this());
  --num_tabs_;
}

void PrintVisitor::Visit(
    std::shared_ptr<LocalVarDeclStmt> local_var_decl_stmt) {
  PrintTabs();
  stream_ << "LocalVarDeclStmt" << std::endl;

  ++num_tabs_;
  local_var_decl_stmt->var_decl->Accept(shared_from_this());
  --num_tabs_;
}

void PrintVisitor::Visit(std::shared_ptr<StmtListStmt> stmt_list_stmt) {
  PrintTabs();
  stream_ << "StmtListStmt" << std::endl;

  ++num_tabs_;
  stmt_list_stmt->stmt_list->Accept(shared_from_this());
  --num_tabs_;
}

void PrintVisitor::Visit(std::shared_ptr<IfStmt> if_stmt) {
  PrintTabs();
  stream_ << "IfStmt" << std::endl;

  ++num_tabs_;
  if_stmt->expr->Accept(shared_from_this());
  if_stmt->stmt->Accept(shared_from_this());
  --num_tabs_;
}

void PrintVisitor::Visit(std::shared_ptr<IfElseStmt> if_else_stmt) {
  PrintTabs();
  stream_ << "IfElseStmt" << std::endl;

  ++num_tabs_;
  if_else_stmt->expr->Accept(shared_from_this());
  if_else_stmt->stmt_true->Accept(shared_from_this());
  if_else_stmt->stmt_false->Accept(shared_from_this());
  --num_tabs_;
}

void PrintVisitor::Visit(std::shared_ptr<WhileStmt> while_stmt) {
  PrintTabs();
  stream_ << "WhileStmt" << std::endl;

  ++num_tabs_;
  while_stmt->expr->Accept(shared_from_this());
  while_stmt->stmt->Accept(shared_from_this());
  --num_tabs_;
}

void PrintVisitor::Visit(std::shared_ptr<PrintStmt> print_stmt) {
  PrintTabs();
  stream_ << "PrintStmt" << std::endl;

  ++num_tabs_;
  print_stmt->expr->Accept(shared_from_this());
  --num_tabs_;
}

void PrintVisitor::Visit(std::shared_ptr<AssignmentStmt> assignment_stmt) {
  PrintTabs();
  stream_ << "AssignmentStmt" << std::endl;

  ++num_tabs_;
  assignment_stmt->lvalue->Accept(shared_from_this());
  assignment_stmt->expr->Accept(shared_from_this());
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
  stream_ << "IntExpr " << int_expr->value << std::endl;
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

void PrintVisitor::Visit(std::shared_ptr<IdentExpr> ident_expr) {
  PrintTabs();
  stream_ << "IdentExpr " << ident_expr->name << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<VarDecl> var_decl) {
  PrintTabs();
  stream_ << "VarDecl " << var_decl->type.type << " " 
          << "is array: " << var_decl->type.is_array << " "
          << var_decl->name << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<Lvalue> lvalue) {
  PrintTabs();
  stream_ << "Lvalue " << lvalue->name << " "
          << "is array: " << lvalue->is_array << std::endl;
}

PrintVisitor::~PrintVisitor() {
  stream_.close();
}

void PrintVisitor::PrintTabs() {
  for (size_t i = 0; i < num_tabs_; stream_ << '\t', ++i);
}
