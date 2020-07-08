#pragma once

#include <memory>

#include "utils/forward_decl.hpp"


class Visitor {
 public:
  virtual void Visit(std::shared_ptr<Program> program) = 0;
  virtual void Visit(std::shared_ptr<MainClass> main_class) = 0;
  virtual void Visit(std::shared_ptr<AssertStmt> assert_stmt) = 0;
  virtual void Visit(std::shared_ptr<LocalVarDeclStmt> local_var_decl_stmt) = 0;
  virtual void Visit(std::shared_ptr<StmtListStmt> stmt_list_stmt) = 0;
  virtual void Visit(std::shared_ptr<IfStmt> if_stmt) = 0;
  virtual void Visit(std::shared_ptr<IfElseStmt> if_else_stmt) = 0;
  virtual void Visit(std::shared_ptr<WhileStmt> while_stmt) = 0;
  virtual void Visit(std::shared_ptr<PrintStmt> print_stmt) = 0;
  virtual void Visit(std::shared_ptr<AssignmentStmt> assignment_stmt) = 0;

  virtual void Visit(std::shared_ptr<BinOpExpr> bin_op_expr) = 0;
  virtual void Visit(std::shared_ptr<SubscriptExpr> subscript_expr) = 0;
  virtual void Visit(std::shared_ptr<LengthExpr> length_expr) = 0;
  virtual void Visit(std::shared_ptr<TrueExpr> true_expr) = 0;
  virtual void Visit(std::shared_ptr<FalseExpr> false_expr) = 0;
  virtual void Visit(std::shared_ptr<IntExpr> int_expr) = 0;
  virtual void Visit(std::shared_ptr<NewExpr> new_expr) = 0;
  virtual void Visit(std::shared_ptr<NewArrayExpr> new_array_expr) = 0;
  virtual void Visit(std::shared_ptr<NotExpr> not_expr) = 0;
  virtual void Visit(std::shared_ptr<IdentExpr> ident_expr) = 0;

  virtual void Visit(std::shared_ptr<ClassDecl> class_decl) = 0;
  virtual void Visit(std::shared_ptr<VarDecl> var_decl) = 0;
  virtual void Visit(std::shared_ptr<Lvalue> lvalue) = 0;
};
