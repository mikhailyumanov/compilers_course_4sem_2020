#pragma once

#include <map>

#include "utils/elements.hpp"
#include "visitors/TemplateVisitor.hpp"


class Interpreter: public TemplateVisitor<int>,
  public std::enable_shared_from_this<Interpreter> {
 public:
  Interpreter();

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

  int GetResult(std::shared_ptr<Program> program);
  int Accept(std::shared_ptr<BasicElement> element) override;

 private:
  void SetTosValue(int value);
  void UnsetTosValue();

 private:
  struct Variable {
    Type type;
    bool is_init = false;
    int value;
  };

  std::map<std::string, Variable> variables;
  int tos_value_;
  bool is_tos_expression_;

};
