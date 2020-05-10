#pragma once

#include <fstream>

#include "visitors/Visitor.hpp"


class PrintVisitor: public Visitor,
  public std::enable_shared_from_this<PrintVisitor> {
 public:
  PrintVisitor(const std::string& filename);

  void Visit(std::shared_ptr<Program> program) override;
  void Visit(std::shared_ptr<MainClass> main_class) override;

  void Visit(std::shared_ptr<PrintStmt> print_stmt) override;

  void Visit(std::shared_ptr<BinOpExpr> bin_op_expr) override;
  void Visit(std::shared_ptr<TrueExpr> true_expr) override;
  void Visit(std::shared_ptr<FalseExpr> false_expr) override;
  void Visit(std::shared_ptr<IntExpr> int_expr) override;
  void Visit(std::shared_ptr<NewExpr> new_expr) override;
  void Visit(std::shared_ptr<NotExpr> not_expr) override;

 ~PrintVisitor();

 private:
  void PrintTabs();
  
 private:
  size_t num_tabs_ = 0;
  std::ofstream stream_;
};
