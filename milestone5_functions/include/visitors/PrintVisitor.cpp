#include "visitors/PrintVisitor.hpp"

#define GO_DOWN GoDown(); if (!as_plugin_) {
#define GO_UP GoUp(); }

PrintVisitor::PrintVisitor(const std::string& filename, bool as_plugin) 
  : stream_(filename), as_plugin_{as_plugin} {
}

PrintVisitor::PrintVisitor(const std::string& filename)
  : PrintVisitor(filename, false) {
}

void PrintVisitor::Visit(std::shared_ptr<Program> element) {
  stream_ << "Program" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: Program")

  GO_DOWN
  element->main_class->Accept(shared_from_this());
  element->class_decl_list->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<MainClass> element) {
  PrintTabs();
  stream_ << "MainClass" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: MainClass")

  GO_DOWN
  element->stmt_list->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<AssertStmt> element) {
  PrintTabs();
  stream_ << "AssertStmt" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: AssertStmt")

  GO_DOWN
  element->expr->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(
    std::shared_ptr<LocalVarDeclStmt> element) {
  PrintTabs();
  stream_ << "LocalVarDeclStmt" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: LocalVarDeclStmt")

  GO_DOWN
  element->var_decl->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<StmtListStmt> element) {
  PrintTabs();
  stream_ << "StmtListStmt" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: StmtListStmt")

  GO_DOWN
  element->stmt_list->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<IfStmt> element) {
  PrintTabs();
  stream_ << "IfStmt" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: IfStmt")

  GO_DOWN
  element->expr->Accept(shared_from_this());
  element->stmt->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<IfElseStmt> element) {
  PrintTabs();
  stream_ << "IfElseStmt" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: IfElseStmt")

  GO_DOWN
  element->expr->Accept(shared_from_this());
  element->stmt_true->Accept(shared_from_this());
  element->stmt_false->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<WhileStmt> element) {
  PrintTabs();
  stream_ << "WhileStmt" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: WhileStmt")

  GO_DOWN
  element->expr->Accept(shared_from_this());
  element->stmt->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<PrintStmt> element) {
  PrintTabs();
  stream_ << "PrintStmt" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: PrintStmt")

  GO_DOWN
  element->expr->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<AssignmentStmt> element) {
  PrintTabs();
  stream_ << "AssignmentStmt" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: AssignmentStmt")

  GO_DOWN
  element->lvalue->Accept(shared_from_this());
  element->expr->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<ReturnStmt> element) {
  PrintTabs();
  stream_ << "ReturnStmt" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: ReturnStmt")

  GO_DOWN
  element->expr->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<MethodStmt> element) {
  PrintTabs();
  stream_ << "MethodStmt" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: MethodStmt")

  GO_DOWN
  element->invocation->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<BinOpExpr> element) {
  PrintTabs();
  stream_ << "BinOpExpr" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: BinOpExpr")

  GO_DOWN
  element->lhs->Accept(shared_from_this());
  PrintTabs(); stream_ << (int) element->op << std::endl;
  element->rhs->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<SubscriptExpr> element) {
  PrintTabs();
  stream_ << "SubscriptExpr" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: SubscriptExpr")

  GO_DOWN
  element->expr->Accept(shared_from_this());
  element->idx->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<LengthExpr> element) {
  PrintTabs();
  stream_ << "LengthExpr" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: LengthExpr")

  GO_DOWN
  element->expr->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<TrueExpr> element) {
  PrintTabs();
  stream_ << "TrueExpr" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: TrueExpr")
}

void PrintVisitor::Visit(std::shared_ptr<FalseExpr> element) {
  PrintTabs();
  stream_ << "FalseExpr" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: FalseExpr")
}

void PrintVisitor::Visit(std::shared_ptr<IntExpr> element) {
  PrintTabs();
  stream_ << "IntExpr " << element->value << std::endl;
  DEBUG_START DEBUG(">>> PrintVisitor: IntExpr") DEBUG(element->value) DEBUG_FINISH
}

void PrintVisitor::Visit(std::shared_ptr<NewExpr> element) {
  PrintTabs();
  stream_ << "NewExpr type = " << element->type << std::endl;
  DEBUG_START DEBUG(">>> PrintVisitor: NewExpr type = ") DEBUG(element->type) DEBUG_FINISH
}

void PrintVisitor::Visit(std::shared_ptr<NewArrayExpr> element) {
  PrintTabs();
  stream_ << "NewArrayExpr type = " << element->type << std::endl;
  DEBUG_START DEBUG(">>> PrintVisitor: NewArrayExpr type = ") DEBUG(element->type) DEBUG_FINISH

  GO_DOWN
  element->expr->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<NotExpr> element) {
  PrintTabs();
  stream_ << "NotExpr" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: NotExpr")

  GO_DOWN
  element->expr->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<IdentExpr> element) {
  PrintTabs();
  stream_ << "IdentExpr " << element->name << std::endl;
  DEBUG_START DEBUG(">>> PrintVisitor: IdentExpr") DEBUG(element->name) DEBUG_FINISH
}

void PrintVisitor::Visit(std::shared_ptr<MethodExpr> element) {
  PrintTabs();
  stream_ << "MethodExpr" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: MethodExpr")

  GO_DOWN
  element->invocation->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<ClassDecl> element) {
  PrintTabs();
  stream_ << "ClassDecl " << element->class_name << std::endl;
  DEBUG_START DEBUG(">>> PrintVisitor: ClassDecl") DEBUG(element->class_name) DEBUG_FINISH

  GO_DOWN
  element->decl_list->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<VarDecl> element) {
  PrintTabs();
  stream_ << "VarDecl " << element->type << " "
          << element->name << std::endl;
  
  DEBUG_START 
    DEBUG(">>> PrintVisitor: VarDecl")
    DEBUG(element->type)
    DEBUG(element->name)
  DEBUG_FINISH
}

void PrintVisitor::Visit(std::shared_ptr<MethodDecl> element) {
  PrintTabs();
  stream_ << "MethodDecl " << element->type << " "
         << element->name << std::endl;

  DEBUG_START
    DEBUG(">>> PrintVisitor: MethodDecl")
    DEBUG(element->type)
    DEBUG(element->name)
  DEBUG_FINISH

  GO_DOWN
  element->stmt_list->Accept(shared_from_this());
  GO_UP
}

void PrintVisitor::Visit(std::shared_ptr<Lvalue> element) {
  PrintTabs();
  
  stream_ << "Lvalue " << element->name << std::endl;
  if (element->expr) {
    GO_DOWN
    element->expr->Accept(shared_from_this());
    GO_UP
  }
}

void PrintVisitor::Visit(std::shared_ptr<MethodInvocation> element) {
  PrintTabs();
  stream_ << "MethodInvocation" << std::endl;
  DEBUG_SINGLE(">>> PrintVisitor: MethodInvocation")

  GO_DOWN
  element->expr->Accept(shared_from_this());
  stream_ << element->name.GetName() << std::endl;
  element->comma_expr_list->Accept(shared_from_this());
  GO_UP
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
