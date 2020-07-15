#pragma once

#include "utils/elements.hpp"
#include "visitors/Visitor.hpp"
#include "visitors/PrintVisitor.hpp"


class SymbolTreeVisitor: public Visitor,
  public std::enable_shared_from_this<SymbolTreeVisitor> {
 public:
  SymbolTreeVisitor();
  SymbolTreeVisitor(const std::string& filename);

  void Visit(std::shared_ptr<Program> element) override;
  void Visit(std::shared_ptr<MainClass> element) override;
  void Visit(std::shared_ptr<AssertStmt> element) override;
  void Visit(std::shared_ptr<LocalVarDeclStmt> element) override;
  void Visit(std::shared_ptr<StmtListStmt> element) override;
  void Visit(std::shared_ptr<IfStmt> element) override;
  void Visit(std::shared_ptr<IfElseStmt> element) override;
  void Visit(std::shared_ptr<WhileStmt> element) override;
  void Visit(std::shared_ptr<PrintStmt> element) override;
  void Visit(std::shared_ptr<AssignmentStmt> element) override;
  void Visit(std::shared_ptr<ReturnStmt> element) override;
  void Visit(std::shared_ptr<MethodStmt> element) override;

  void Visit(std::shared_ptr<BinOpExpr> element) override;
  void Visit(std::shared_ptr<SubscriptExpr> element) override;
  void Visit(std::shared_ptr<LengthExpr> element) override;
  void Visit(std::shared_ptr<TrueExpr> element) override;
  void Visit(std::shared_ptr<FalseExpr> element) override;
  void Visit(std::shared_ptr<IntExpr> element) override;
  void Visit(std::shared_ptr<NewExpr> element) override;
  void Visit(std::shared_ptr<NewArrayExpr> element) override;
  void Visit(std::shared_ptr<NotExpr> element) override;
  void Visit(std::shared_ptr<IdentExpr> element) override;

  void Visit(std::shared_ptr<ClassDecl> element) override;
  void Visit(std::shared_ptr<VarDecl> element) override;
  void Visit(std::shared_ptr<Lvalue> element) override;

  std::shared_ptr<ScopeLayerTree> GetTree() const;

 private:
  void ScopeDown();
  void ScopeUp();

  friend class Interpreter;

 private:
  std::shared_ptr<ScopeLayerTree> tree_;
  ScopeLayerTree::Iterator current_scope_;

  // verbose
  std::shared_ptr<PrintVisitor> print_visitor_;
  bool verbose_ = false;
};