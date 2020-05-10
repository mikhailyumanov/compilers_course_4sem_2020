#pragma once

#include <memory>

#include "utils/forward_decl.hpp"


class Visitor {
 public:
  virtual void Visit(std::shared_ptr<Program> program) = 0;
  virtual void Visit(std::shared_ptr<MainClass> main_class) = 0;
  virtual void Visit(std::shared_ptr<PrintStmt> print_stmt) = 0;
  virtual void Visit(std::shared_ptr<BinOpExpr> bin_op_expr) = 0;
  virtual void Visit(std::shared_ptr<TrueExpr> true_expr) = 0;
  virtual void Visit(std::shared_ptr<FalseExpr> false_expr) = 0;
  virtual void Visit(std::shared_ptr<IntExpr> int_expr) = 0;
  virtual void Visit(std::shared_ptr<NewExpr> new_expr) = 0;
  virtual void Visit(std::shared_ptr<NotExpr> not_expr) = 0;
};
