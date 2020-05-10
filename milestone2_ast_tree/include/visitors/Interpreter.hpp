#pragma once

#include <map>

#include "utils/elements.hpp"
#include "visitors/Visitor.hpp"


class Interpreter: public Visitor,
  public std::enable_shared_from_this<Interpreter> {
 public:
  Interpreter();

  void Visit(std::shared_ptr<Program> program) override;
  void Visit(std::shared_ptr<MainClass> main_class) override;
  void Visit(std::shared_ptr<PrintStmt> print_stmt) override;
  void Visit(std::shared_ptr<BinOpExpr> bin_op_expr) override;
  void Visit(std::shared_ptr<TrueExpr> true_expr) override;
  void Visit(std::shared_ptr<FalseExpr> false_expr) override;
  void Visit(std::shared_ptr<IntExpr> int_expr) override;
  void Visit(std::shared_ptr<NewExpr> new_expr) override;
  void Visit(std::shared_ptr<NotExpr> not_expr) override;

  int GetResult(std::shared_ptr<Program> program);

 private:
  void SetTosValue(int value);
  void UnsetTosValue();

 private:
  std::map<std::string, int> variables;
  int tos_value_;
  bool is_tos_expression_;

};
