#pragma once

#include <fstream>

#include "utils/elements.hpp"
#include "visitors/Visitor.hpp"


class PrintVisitor: public Visitor,
  public std::enable_shared_from_this<PrintVisitor> {
 public:
  PrintVisitor() = default;
  PrintVisitor(const std::string& filename);
  PrintVisitor(const std::string& filename, bool as_plugin);

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
  void Visit(std::shared_ptr<MethodExpr> element) override;

  void Visit(std::shared_ptr<VarDecl> element) override;
  void Visit(std::shared_ptr<MethodDecl> element) override;
  void Visit(std::shared_ptr<ClassDecl> element) override;
  void Visit(std::shared_ptr<Lvalue> element) override;
  void Visit(std::shared_ptr<MethodInvocation> element) override;

 ~PrintVisitor();

  void PrintTabs();
  std::ofstream& GetStream();

  void GoDown();
  void GoUp();

 private:
  size_t num_tabs_ = 0;
  std::ofstream stream_;
  bool as_plugin_ = false;
};
