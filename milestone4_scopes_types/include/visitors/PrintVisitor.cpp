#include "visitors/PrintVisitor.hpp"

PrintVisitor::PrintVisitor(const std::string& filename, bool as_plugin) 
  : stream_(filename), as_plugin_{as_plugin} {
}

PrintVisitor::PrintVisitor(const std::string& filename)
  : PrintVisitor(filename, false) {
}

void PrintVisitor::Visit(std::shared_ptr<Program> program) {
  stream_ << "Program" << std::endl;

  GoDown(); if (!as_plugin_) {
  program->main_class->Accept(shared_from_this());
  program->class_decl_list->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<MainClass> main_class) {
  PrintTabs();
  stream_ << "MainClass" << std::endl;

  GoDown(); if (!as_plugin_) {
  main_class->stmt_list->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<AssertStmt> assert_stmt) {
  PrintTabs();
  stream_ << "AssertStmt" << std::endl;

  GoDown(); if (!as_plugin_) {
  assert_stmt->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(
    std::shared_ptr<LocalVarDeclStmt> local_var_decl_stmt) {
  PrintTabs();
  stream_ << "LocalVarDeclStmt" << std::endl;

  GoDown(); if (!as_plugin_) {
  local_var_decl_stmt->var_decl->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<StmtListStmt> stmt_list_stmt) {
  PrintTabs();
  stream_ << "StmtListStmt" << std::endl;

  GoDown(); if (!as_plugin_) {
  stmt_list_stmt->stmt_list->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<IfStmt> if_stmt) {
  PrintTabs();
  stream_ << "IfStmt" << std::endl;

  GoDown(); if (!as_plugin_) {
  if_stmt->expr->Accept(shared_from_this());
  if_stmt->stmt->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<IfElseStmt> if_else_stmt) {
  PrintTabs();
  stream_ << "IfElseStmt" << std::endl;

  GoDown(); if (!as_plugin_) {
  if_else_stmt->expr->Accept(shared_from_this());
  if_else_stmt->stmt_true->Accept(shared_from_this());
  if_else_stmt->stmt_false->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<WhileStmt> while_stmt) {
  PrintTabs();
  stream_ << "WhileStmt" << std::endl;

  GoDown(); if (!as_plugin_) {
  while_stmt->expr->Accept(shared_from_this());
  while_stmt->stmt->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<PrintStmt> print_stmt) {
  PrintTabs();
  stream_ << "PrintStmt" << std::endl;

  GoDown(); if (!as_plugin_) {
  print_stmt->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<AssignmentStmt> assignment_stmt) {
  PrintTabs();
  stream_ << "AssignmentStmt" << std::endl;

  GoDown(); if (!as_plugin_) {
  assignment_stmt->lvalue->Accept(shared_from_this());
  assignment_stmt->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<BinOpExpr> bin_op_expr) {
  PrintTabs();
  stream_ << "BinOpExpr" << std::endl;

  GoDown(); if (!as_plugin_) {
  bin_op_expr->lhs->Accept(shared_from_this());
  PrintTabs(); stream_ << (int) bin_op_expr->op << std::endl;
  bin_op_expr->rhs->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<SubscriptExpr> subscript_expr) {
  PrintTabs();
  stream_ << "SubscriptExpr" << std::endl;

  GoDown(); if (!as_plugin_) {
  subscript_expr->expr->Accept(shared_from_this());
  subscript_expr->idx->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<LengthExpr> length_expr) {
  PrintTabs();
  stream_ << "LengthExpr" << std::endl;

  GoDown(); if (!as_plugin_) {
  length_expr->expr->Accept(shared_from_this());
  GoUp(); }
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
  stream_ << "NewExpr type = " << new_expr->type << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<NewArrayExpr> new_array_expr) {
  PrintTabs();
  stream_ << "NewArrayExpr type = " << new_array_expr->type << std::endl;

  GoDown(); if (!as_plugin_) {
  new_array_expr->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<NotExpr> not_expr) {
  PrintTabs();
  stream_ << "NotExpr" << std::endl;

  GoDown(); if (!as_plugin_) {
  not_expr->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<IdentExpr> ident_expr) {
  PrintTabs();
  stream_ << "IdentExpr " << ident_expr->name << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<ClassDecl> class_decl) {
  PrintTabs();
  stream_ << "ClassDecl " << class_decl->class_name << std::endl;

  GoDown(); if (!as_plugin_) {
  class_decl->decl_list->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<VarDecl> var_decl) {
  PrintTabs();
  stream_ << "VarDecl " << var_decl->type.type << " " 
          << "is array: " << var_decl->type.is_array << " "
          << var_decl->name << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<Lvalue> lvalue) {
  PrintTabs();
  
  stream_ << "Lvalue " << lvalue->name << std::endl;
  if (lvalue->expr) {
    GoDown(); if (!as_plugin_) {
    lvalue->expr->Accept(shared_from_this());
    GoUp(); }
  }
}

PrintVisitor::~PrintVisitor() {
  stream_.close();
}

void PrintVisitor::PrintTabs() {
  for (size_t i = 0; i < num_tabs_; stream_ << '\t', ++i);
}

std::ofstream& PrintVisitor::GetStream() {
  return stream_;
}

void PrintVisitor::GoDown() {
  ++num_tabs_;
}

void PrintVisitor::GoUp() {
  --num_tabs_;
}
