#pragma once

#include <memory>

#include "utils/forward_decl.hpp"


class Visitor {
 public:
  virtual void Visit(std::shared_ptr<Program> element) = 0;
  virtual void Visit(std::shared_ptr<MainClass> element) = 0;
  virtual void Visit(std::shared_ptr<AssertStmt> element) = 0;
  virtual void Visit(std::shared_ptr<LocalVarDeclStmt> element) = 0;
  virtual void Visit(std::shared_ptr<StmtListStmt> element) = 0;
  virtual void Visit(std::shared_ptr<IfStmt> element) = 0;
  virtual void Visit(std::shared_ptr<IfElseStmt> element) = 0;
  virtual void Visit(std::shared_ptr<WhileStmt> element) = 0;
  virtual void Visit(std::shared_ptr<PrintStmt> element) = 0;
  virtual void Visit(std::shared_ptr<AssignmentStmt> element) = 0;
  virtual void Visit(std::shared_ptr<ReturnStmt> element) = 0;
  virtual void Visit(std::shared_ptr<MethodStmt> element) = 0;

  virtual void Visit(std::shared_ptr<BinOpExpr> element) = 0;
  virtual void Visit(std::shared_ptr<SubscriptExpr> element) = 0;
  virtual void Visit(std::shared_ptr<LengthExpr> element) = 0;
  virtual void Visit(std::shared_ptr<TrueExpr> element) = 0;
  virtual void Visit(std::shared_ptr<FalseExpr> element) = 0;
  virtual void Visit(std::shared_ptr<IntExpr> element) = 0;
  virtual void Visit(std::shared_ptr<NewExpr> element) = 0;
  virtual void Visit(std::shared_ptr<NewArrayExpr> element) = 0;
  virtual void Visit(std::shared_ptr<NotExpr> element) = 0;
  virtual void Visit(std::shared_ptr<IdentExpr> element) = 0;
  virtual void Visit(std::shared_ptr<MethodExpr> element) = 0;
  virtual void Visit(std::shared_ptr<ThisExpr> element) = 0;

  virtual void Visit(std::shared_ptr<VarDecl> element) = 0;
  virtual void Visit(std::shared_ptr<MethodDecl> element) = 0;
  virtual void Visit(std::shared_ptr<ClassDecl> element) = 0;
  virtual void Visit(std::shared_ptr<Lvalue> element) = 0;
  virtual void Visit(std::shared_ptr<MethodInvocation> element) = 0;
};
