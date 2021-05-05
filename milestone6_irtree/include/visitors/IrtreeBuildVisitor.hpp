//
// Created by akhtyamovpavel on 4/8/20.
//

#pragma once

#include <unordered_map>

#include "include/visitors/Visitor.hpp"
#include "irtree/tree_wrappers/SubtreeWrapper.hpp"
#include "functions/FrameTranslator.hpp"
#include "scopes/ScopeLayerTree.hpp"
#include "visitors/TemplateVisitor.hpp"
#include "visitors/SymbolTreeVisitor.hpp"

using IrtMapping = 
  std::unordered_map<std::string, std::shared_ptr<IRT::Statement>>;


class IrtreeBuildVisitor:
  public TemplateVisitor<std::shared_ptr<IRT::SubtreeWrapper>>,
  public std::enable_shared_from_this<IrtreeBuildVisitor> {
 public:
  explicit IrtreeBuildVisitor(const std::string& filename);
  IrtreeBuildVisitor();

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
  void Visit(std::shared_ptr<ThisExpr> element) override;

  void Visit(std::shared_ptr<VarDecl> element) override;
  void Visit(std::shared_ptr<MethodDecl> element) override;
  void Visit(std::shared_ptr<ClassDecl> element) override;
  void Visit(std::shared_ptr<Lvalue> element) override;
  void Visit(std::shared_ptr<MethodInvocation> element) override;

  void VisitStmtList(std::shared_ptr<BasicList> element);

  IrtMapping GetTrees();

  std::shared_ptr<IRT::SubtreeWrapper> Accept(
    std::shared_ptr<BasicElement> element) override;


 private:
  std::shared_ptr<IRT::Expression> Subscript(
    std::shared_ptr<IRT::Expression> var_expr,
    std::shared_ptr<IRT::Expression> idx_expr) const;

 private:
  std::unordered_map<std::string, std::shared_ptr<IRT::FrameTranslator>>
    frame_translator_;

  std::shared_ptr<IRT::FrameTranslator> current_frame_;
  std::shared_ptr<ScopeLayerTree> tree_;

  IrtMapping method_trees_;

  std::shared_ptr<SymbolTreeVisitor> symbol_tree_visitor_;
  std::string current_class_;
  bool method_decl_ = false;

  std::string main_class_ = "::main_class";
};


