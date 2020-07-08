#pragma once

#include "utils/elements.hpp"
#include "visitors/Visitor.hpp"


class SymbolTreeVisitor: public Visitor,
  public std::enable_shared_from_this<SymbolTreeVisitor> {
 public:
  SymbolTreeVisitor(const std::string& filename);

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
  void Visit(std::shared_ptr<TrueExpr> true_expr) override;
  void Visit(std::shared_ptr<FalseExpr> false_expr) override;
  void Visit(std::shared_ptr<IntExpr> int_expr) override;
  void Visit(std::shared_ptr<NewExpr> new_expr) override;
  void Visit(std::shared_ptr<NotExpr> not_expr) override;
  void Visit(std::shared_ptr<IdentExpr> ident_expr) override;
  void Visit(std::shared_ptr<ClassDecl> class_decl) override;
  void Visit(std::shared_ptr<VarDecl> var_decl) override;
  void Visit(std::shared_ptr<Lvalue> lvalue) override;

 private:
  void ScopeDown(const std::string& name);
  void ScopeUp();

 private:
  std::shared_ptr<ScopeLayer> current_scope_;
  std::shared_ptr<ScopeLayerTree> tree_;

 // verbose
 private:
  void PrintTabs() const;
  size_t num_tabs_;
};
