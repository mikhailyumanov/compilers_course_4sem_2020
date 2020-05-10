#include "visitors/Interpreter.hpp"


Interpreter::Interpreter() : tos_value_{0}, is_tos_expression_{false} {
}

void Interpreter::Visit(std::shared_ptr<Program> program) {
  program->class_decl_list->Accept(shared_from_this());
  program->main_class->Accept(shared_from_this());
}

void Interpreter::Visit(std::shared_ptr<MainClass> main_class) {
  main_class->stmt_list->Accept(shared_from_this());
}

void Interpreter::Visit(std::shared_ptr<PrintStmt> print_stmt) {
  print_stmt->expr->Accept(shared_from_this());
  std::cout << "Print: " << tos_value_ << std::endl;

  UnsetTosValue();
}

void Interpreter::Visit(std::shared_ptr<BinOpExpr> bin_op_expr) {
  bin_op_expr->lhs->Accept(shared_from_this());
  int lhs = tos_value_;
  bin_op_expr->rhs->Accept(shared_from_this());
  int rhs = tos_value_;
  
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
  not_expr->expr->Accept(shared_from_this());
  SetTosValue(!tos_value_);
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
