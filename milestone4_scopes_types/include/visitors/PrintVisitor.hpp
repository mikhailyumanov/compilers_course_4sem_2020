#pragma once

#include <fstream>

#include "utils/elements.hpp"
#include "visitors/Visitor.hpp"


class PrintVisitor: public Visitor,
  public std::enable_shared_from_this<PrintVisitor> {
 public:
  PrintVisitor(const std::string& filename);

  void Visit(std::shared_ptr<Program> program) override;
  void Visit(std::shared_ptr<MainClass> main_class) override;
  void Visit(std::shared_ptr<AssertStmt> assert_stmt) override;
  void Visit(std::shared_ptr<LocalVarDeclStmt> local_var_decl_stmt) override;
  void Visit(std::shared_ptr<StmtListStmt> stmt_list_stmt) override;
  void Visit(std::shared_ptr<IfStmt> if_stmt) override;
  void Visit(std::shared_ptr<IfElseStmt> if_else_stmt) override;
  void Visit(std::shared_ptr<WhileStmt> while_stmt) override;
  void Visit(std::shared_ptr<PrintStmt> print_stmt) override;
  void Visit(std::shared_ptr<AssignmentStmt> assignment_stmt) override;

  void Visit(std::shared_ptr<BinOpExpr> bin_op_expr) override;
  void Visit(std::shared_ptr<SubscriptExpr> subscript_expr) override;
  void Visit(std::shared_ptr<LengthExpr> length_expr) override;
  void Visit(std::shared_ptr<TrueExpr> true_expr) override;
  void Visit(std::shared_ptr<FalseExpr> false_expr) override;
  void Visit(std::shared_ptr<IntExpr> int_expr) override;
  void Visit(std::shared_ptr<NewExpr> new_expr) override;
  void Visit(std::shared_ptr<NewArrayExpr> new_array_expr) override;
  void Visit(std::shared_ptr<NotExpr> not_expr) override;
  void Visit(std::shared_ptr<IdentExpr> ident_expr) override;

  void Visit(std::shared_ptr<ClassDecl> class_decl) override;
  void Visit(std::shared_ptr<VarDecl> var_decl) override;
  void Visit(std::shared_ptr<Lvalue> lvalue) override;

 ~PrintVisitor();

 private:
  void PrintTabs();
  
 private:
  size_t num_tabs_ = 0;
  std::ofstream stream_;
};
