#include "visitors/PrintVisitor.hpp"

PrintVisitor::PrintVisitor(const std::string& filename, bool as_plugin) 
  : stream_(filename), as_plugin_{as_plugin} {
}

PrintVisitor::PrintVisitor(const std::string& filename)
  : PrintVisitor(filename, false) {
}

void PrintVisitor::Visit(std::shared_ptr<Program> element) {
  stream_ << "Program" << std::endl;
  DEBUG_SINGLE("Program")

  GoDown(); if (!as_plugin_) {
  element->main_class->Accept(shared_from_this());
  element->class_decl_list->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<MainClass> element) {
  PrintTabs();
  stream_ << "MainClass" << std::endl;
  DEBUG_SINGLE("MainClass")

  GoDown(); if (!as_plugin_) {
  element->stmt_list->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<AssertStmt> element) {
  PrintTabs();
  stream_ << "AssertStmt" << std::endl;
  DEBUG_SINGLE("AssertStmt")

  GoDown(); if (!as_plugin_) {
  element->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(
    std::shared_ptr<LocalVarDeclStmt> element) {
  PrintTabs();
  stream_ << "LocalVarDeclStmt" << std::endl;
  DEBUG_SINGLE("LocalVarDeclStmt")

  GoDown(); if (!as_plugin_) {
  element->var_decl->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<StmtListStmt> element) {
  PrintTabs();
  stream_ << "StmtListStmt" << std::endl;
  DEBUG_SINGLE("StmtListStmt")

  GoDown(); if (!as_plugin_) {
  element->stmt_list->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<IfStmt> element) {
  PrintTabs();
  stream_ << "IfStmt" << std::endl;
  DEBUG_SINGLE("IfStmt")

  GoDown(); if (!as_plugin_) {
  element->expr->Accept(shared_from_this());
  element->stmt->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<IfElseStmt> element) {
  PrintTabs();
  stream_ << "IfElseStmt" << std::endl;
  DEBUG_SINGLE("IfElseStmt")

  GoDown(); if (!as_plugin_) {
  element->expr->Accept(shared_from_this());
  element->stmt_true->Accept(shared_from_this());
  element->stmt_false->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<WhileStmt> element) {
  PrintTabs();
  stream_ << "WhileStmt" << std::endl;
  DEBUG_SINGLE("WhileStmt")

  GoDown(); if (!as_plugin_) {
  element->expr->Accept(shared_from_this());
  element->stmt->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<PrintStmt> element) {
  PrintTabs();
  stream_ << "PrintStmt" << std::endl;
  DEBUG_SINGLE("PrintStmt")

  GoDown(); if (!as_plugin_) {
  element->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<AssignmentStmt> element) {
  PrintTabs();
  stream_ << "AssignmentStmt" << std::endl;
  DEBUG_SINGLE("AssignmentStmt")

  GoDown(); if (!as_plugin_) {
  element->lvalue->Accept(shared_from_this());
  element->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<ReturnStmt> element) {
  PrintTabs();
  stream_ << "ReturnStmt" << std::endl;
  DEBUG_SINGLE("ReturnStmt")

  GoDown(); if (!as_plugin_) {
  element->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<MethodStmt> element) {
  PrintTabs();
  stream_ << "MethodStmt" << std::endl;
  DEBUG_SINGLE("MethodStmt")

  GoDown(); if (!as_plugin_) {
  element->invocation->expr->Accept(shared_from_this());
  stream_ << element->invocation->name.GetName() << std::endl;
  element->invocation->comma_expr_list->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<BinOpExpr> element) {
  PrintTabs();
  stream_ << "BinOpExpr" << std::endl;
  DEBUG_SINGLE("BinOpExpr")

  GoDown(); if (!as_plugin_) {
  element->lhs->Accept(shared_from_this());
  PrintTabs(); stream_ << (int) element->op << std::endl;
  element->rhs->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<SubscriptExpr> element) {
  PrintTabs();
  stream_ << "SubscriptExpr" << std::endl;
  DEBUG_SINGLE("SubscriptExpr")

  GoDown(); if (!as_plugin_) {
  element->expr->Accept(shared_from_this());
  element->idx->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<LengthExpr> element) {
  PrintTabs();
  stream_ << "LengthExpr" << std::endl;
  DEBUG_SINGLE("LengthExpr")

  GoDown(); if (!as_plugin_) {
  element->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<TrueExpr> element) {
  PrintTabs();
  stream_ << "TrueExpr" << std::endl;
}

void PrintVisitor::Visit(std::shared_ptr<FalseExpr> element) {
  PrintTabs();
  stream_ << "FalseExpr" << std::endl;
  DEBUG_SINGLE("FalseExpr")
}

void PrintVisitor::Visit(std::shared_ptr<IntExpr> element) {
  PrintTabs();
  stream_ << "IntExpr " << element->value << std::endl;
  DEBUG_START DEBUG("IntExpr") DEBUG(element->value) DEBUG_FINISH
}

void PrintVisitor::Visit(std::shared_ptr<NewExpr> element) {
  PrintTabs();
  stream_ << "NewExpr type = " << element->type << std::endl;
  DEBUG_START DEBUG("NewExpr type = ") DEBUG(element->type) DEBUG_FINISH
}

void PrintVisitor::Visit(std::shared_ptr<NewArrayExpr> element) {
  PrintTabs();
  stream_ << "NewArrayExpr type = " << element->type << std::endl;
  DEBUG_START DEBUG("NewArrayExpr type = ") DEBUG(element->type) DEBUG_FINISH

  GoDown(); if (!as_plugin_) {
  element->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<NotExpr> element) {
  PrintTabs();
  stream_ << "NotExpr" << std::endl;
  DEBUG_SINGLE("NotExpr")

  GoDown(); if (!as_plugin_) {
  element->expr->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<IdentExpr> element) {
  PrintTabs();
  stream_ << "IdentExpr " << element->name << std::endl;
  DEBUG_START DEBUG("IdentExpr") DEBUG(element->name) DEBUG_FINISH
}

void PrintVisitor::Visit(std::shared_ptr<ClassDecl> element) {
  PrintTabs();
  stream_ << "ClassDecl " << element->class_name << std::endl;
  DEBUG_START DEBUG("ClassDecl") DEBUG(element->class_name) DEBUG_FINISH

  GoDown(); if (!as_plugin_) {
  element->decl_list->Accept(shared_from_this());
  GoUp(); }
}

void PrintVisitor::Visit(std::shared_ptr<VarDecl> element) {
  PrintTabs();
  stream_ << "VarDecl " << element->type.type << " " 
          << "is array: " << element->type.is_array << " "
          << element->name << std::endl;
  
  DEBUG_START 
    DEBUG("VarDecl")
    DEBUG(element->type.type)
    DEBUG("is array: ")
    DEBUG(element->type.is_array)
    DEBUG(element->name)
  DEBUG_FINISH
}

void PrintVisitor::Visit(std::shared_ptr<Lvalue> element) {
  PrintTabs();
  
  stream_ << "Lvalue " << element->name << std::endl;
  if (element->expr) {
    GoDown(); if (!as_plugin_) {
    element->expr->Accept(shared_from_this());
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