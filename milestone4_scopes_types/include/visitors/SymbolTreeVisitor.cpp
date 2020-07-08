#include "visitors/SymbolTreeVisitor.hpp"


SymbolTreeVisitor::SymbolTreeVisitor(const std::string& filename) 
  : current_scope_{}, tree_{current_scope_} {
}

void SymbolTreeVisitor::Visit(std::shared_ptr<Program> program) {
  // current_scope_ = main() scope

  program->main_class->Accept(shared_from_this());
  program->class_decl_list->Accept(shared_from_this());
}

void SymbolTreeVisitor::Visit(std::shared_ptr<MainClass> main_class) {
  // current_scope_ = main() scope

  main_class->stmt_list->Accept(shared_from_this());
}

void SymbolTreeVisitor::Visit(std::shared_ptr<AssertStmt> assert_stmt) {
  assert_stmt->expr->Accept(shared_from_this());
}

void SymbolTreeVisitor::Visit(
    std::shared_ptr<LocalVarDeclStmt> local_var_decl_stmt) {
  local_var_decl_stmt->var_decl->Accept(shared_from_this());
}

void SymbolTreeVisitor::Visit(std::shared_ptr<StmtListStmt> stmt_list_stmt) {
  ScopeDown();
  stmt_list_stmt->stmt_list->Accept(shared_from_this());
  ScopeUp();
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IfStmt> if_stmt) {
  if_stmt->expr->Accept(shared_from_this());

  ScopeDown();
  if_stmt->stmt->Accept(shared_from_this());
  ScopeUp();
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IfElseStmt> if_else_stmt) {
  if_else_stmt->expr->Accept(shared_from_this());

  ScopeDown();
  if_else_stmt->stmt_true->Accept(shared_from_this());
  ScopeUp();

  ScopeDown();
  if_else_stmt->stmt_false->Accept(shared_from_this());
  ScopeUp();
}

void SymbolTreeVisitor::Visit(std::shared_ptr<WhileStmt> while_stmt) {
  while_stmt->expr->Accept(shared_from_this());

  ScopeDown();
  while_stmt->stmt->Accept(shared_from_this());
  ScopeUp();
}

void SymbolTreeVisitor::Visit(std::shared_ptr<PrintStmt> print_stmt) {
  print_stmt->expr->Accept(shared_from_this());
}

void SymbolTreeVisitor::Visit(std::shared_ptr<AssignmentStmt> assignment_stmt) {
  assignment_stmt->lvalue->Accept(shared_from_this());
  assignment_stmt->expr->Accept(shared_from_this());
}

void SymbolTreeVisitor::Visit(std::shared_ptr<BinOpExpr> bin_op_expr) {
  bin_op_expr->lhs->Accept(shared_from_this());
  std::cout << (int) bin_op_expr->op << std::endl;
  bin_op_expr->rhs->Accept(shared_from_this());
}

void SymbolTreeVisitor::Visit(std::shared_ptr<TrueExpr> true_expr) {
  // do nothing
}

void SymbolTreeVisitor::Visit(std::shared_ptr<FalseExpr> false_expr) {
  // do nothing
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IntExpr> int_expr) {
  // do nothing
}

void SymbolTreeVisitor::Visit(std::shared_ptr<NewExpr> new_expr) {
}

void SymbolTreeVisitor::Visit(std::shared_ptr<NotExpr> not_expr) {
  not_expr->expr->Accept(shared_from_this());
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IdentExpr> ident_expr) {
  current_scope_->GetSymbol(ident_expr->name);
}

void SymbolTreeVisitor::Visit(std::shared_ptr<ClassDecl> class_decl) {
  ScopeDown();
  class_decl->decl_list->Accept(shared_from_this());
  ScopeUp();
}

void SymbolTreeVisitor::Visit(std::shared_ptr<VarDecl> var_decl) {
  if (current_scope_->IsDeclared(var_decl->name)) {
    throw std::runtime_error("Variable is declared");
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<Lvalue> lvalue) {
  // TODO
}

void SymbolTreeVisitor::ScopeDown(const std::string& name = "") {
  PrintTabs();
  ++num_tabs_;
  std::cout << name << std::endl;

  auto new_scope = std::make_shared<ScopeLayer>(current_scope_);
  current_scope_ = new_scope;
}

void SymbolTreeVisitpr::ScopeUp() {
  --num_tabs;

  current_scope_ = current_scope_->GetParent();
}

void SymbolTreeVisitor::PrintTabs() const {
  for (size_t i = 0; i < num_tabs_; stream_ << '\t', ++i);
}
