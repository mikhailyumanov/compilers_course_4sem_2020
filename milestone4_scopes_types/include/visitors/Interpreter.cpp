#include "visitors/Interpreter.hpp"


struct AssertException {};

Interpreter::Interpreter() : tos_value_{0}, is_tos_expression_{false} {
}

void Interpreter::Visit(std::shared_ptr<Program> program) {
  program->class_decl_list->Accept(Interpreter::shared_from_this());
  program->main_class->Accept(shared_from_this());
}

void Interpreter::Visit(std::shared_ptr<MainClass> main_class) {
  main_class->stmt_list->Accept(shared_from_this());
}

void Interpreter::Visit(std::shared_ptr<AssertStmt> assert_stmt) {
  if (!Accept(assert_stmt->expr)) {
    throw AssertException();
  }
}

void Interpreter::Visit(
    std::shared_ptr<LocalVarDeclStmt> local_var_decl_stmt) {
  local_var_decl_stmt->var_decl->Accept(shared_from_this());
}

void Interpreter::Visit(std::shared_ptr<StmtListStmt> stmt_list_stmt) {
  stmt_list_stmt->stmt_list->Accept(shared_from_this());
}

void Interpreter::Visit(std::shared_ptr<IfStmt> if_stmt) {
  if (Accept(if_stmt->expr)) { 
    if_stmt->stmt->Accept(shared_from_this()); 
  }
}

void Interpreter::Visit(std::shared_ptr<IfElseStmt> if_else_stmt) {
  if (Accept(if_else_stmt->expr)) { 
    tos_value_ = Accept(if_else_stmt->stmt_true);
  } else {
    tos_value_ = Accept(if_else_stmt->stmt_false);
  }
}

void Interpreter::Visit(std::shared_ptr<WhileStmt> while_stmt) {
  while_stmt->expr->Accept(shared_from_this());
  while (Accept(while_stmt->expr)) { 
    while_stmt->stmt->Accept(shared_from_this()); 
  }
}

void Interpreter::Visit(std::shared_ptr<PrintStmt> print_stmt) {
  std::cout << Accept(print_stmt->expr) << std::endl;
  UnsetTosValue();
}

void Interpreter::Visit(std::shared_ptr<AssignmentStmt> assignment_stmt) {
  variables[assignment_stmt->lvalue->name].value =
      Accept(assignment_stmt->expr);
  variables[assignment_stmt->lvalue->name].is_init = true;
}

void Interpreter::Visit(std::shared_ptr<BinOpExpr> bin_op_expr) {
  int lhs = Accept(bin_op_expr->lhs);
  int rhs = Accept(bin_op_expr->rhs);
  
  int tmp = 0;
  switch(bin_op_expr->op) {
    case BinOpExpr::Operation::OP_AND:     tmp = lhs && rhs; break;
    case BinOpExpr::Operation::OP_OR:      tmp = lhs || rhs; break;
    case BinOpExpr::Operation::OP_LESS:    tmp = lhs <  rhs; break;
    case BinOpExpr::Operation::OP_GREATER: tmp = lhs >  rhs; break;
    case BinOpExpr::Operation::OP_EQUAL:   tmp = lhs == rhs; break;
    case BinOpExpr::Operation::OP_PLUS:    tmp = lhs +  rhs; break;
    case BinOpExpr::Operation::OP_MINUS:   tmp = lhs -  rhs; break;
    case BinOpExpr::Operation::OP_STAR:    tmp = lhs *  rhs; break;
    case BinOpExpr::Operation::OP_SLASH:   tmp = lhs /  rhs; break;
    case BinOpExpr::Operation::OP_RMNDR:   tmp = lhs %  rhs; break;
    default: break;
  }

  SetTosValue(tmp);
}

void Interpreter::Visit(std::shared_ptr<TrueExpr> true_expr) {
  SetTosValue(true);
}

void Interpreter::Visit(std::shared_ptr<FalseExpr> false_expr) {
  SetTosValue(false);
}

void Interpreter::Visit(std::shared_ptr<IntExpr> int_expr) {
  SetTosValue(int_expr->value);
}

void Interpreter::Visit(std::shared_ptr<NewExpr> new_expr) {}

void Interpreter::Visit(std::shared_ptr<NotExpr> not_expr) {
  SetTosValue(!Accept(not_expr->expr));
}

void Interpreter::Visit(std::shared_ptr<IdentExpr> ident_expr) {
  SetTosValue(variables[ident_expr->name].value);
}

void Interpreter::Visit(std::shared_ptr<VarDecl> var_decl) {
  UnsetTosValue();
  variables[var_decl->name] = {var_decl->type, false, 0};
}
 
void Interpreter::Visit(std::shared_ptr<Lvalue> lvalue) {
  // do nothing
}

void Interpreter::SetTosValue(int value){
  tos_value_ = value;
  is_tos_expression_ = true;
}

void Interpreter::UnsetTosValue(){
  tos_value_ = 0;
  is_tos_expression_ = false;
}

int Interpreter::GetResult(std::shared_ptr<Program> program) {
  UnsetTosValue();
  Visit(program);

  return tos_value_;
}

int Interpreter::Accept(std::shared_ptr<BasicElement> element) {
  element->Accept(shared_from_this());
  return tos_value_;
}
