#pragma once

#include <map>

#include "utils/elements.hpp"
#include "visitors/TemplateVisitor.hpp"
#include "visitors/SymbolTreeVisitor.hpp"

#include "types/Object.hpp"
#include "types/Integer.hpp"
#include "types/Bool.hpp"
#include "types/Class.hpp"


class Interpreter: public TemplateVisitor<std::shared_ptr<Object>>,
  public std::enable_shared_from_this<Interpreter> {
 public:
  Interpreter();
  Interpreter(const std::string& filename);

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

  int GetResult(std::shared_ptr<Program> program);
  std::shared_ptr<Object> Accept(std::shared_ptr<BasicElement> element) override;

 private:
  void SetTosValue(std::shared_ptr<Object> value);
  void UnsetTosValue();

 private:
  std::shared_ptr<Object> tos_value_;
  std::shared_ptr<SymbolTreeVisitor> symbol_tree_visitor_;
  ScopeLayerTree::Iterator current_scope_;
};
