#pragma once

#include "statements/Statement.hpp"
#include "expressions/Expression.hpp"


class IfStmt: public Statement,
  public std::enable_shared_from_this<IfStmt> {
 public:
  IfStmt(std::shared_ptr<Expression> expr, std::shared_ptr<Statement> stmt);

  void Perform() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Expression> expr;
  std::shared_ptr<Statement> stmt;
};


class IfElseStmt: public Statement,
  public std::enable_shared_from_this<IfElseStmt> {
 public:
  IfElseStmt(std::shared_ptr<Expression> expr, 
      std::shared_ptr<Statement> stmt_true, 
      std::shared_ptr<Statement> stmt_false);

  void Perform() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Expression> expr;
  std::shared_ptr<Statement> stmt_true;
  std::shared_ptr<Statement> stmt_false;
};


class WhileStmt: public Statement,
  public std::enable_shared_from_this<WhileStmt> {
 public:
  WhileStmt(std::shared_ptr<Expression> expr, std::shared_ptr<Statement> stmt);

  void Perform() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Expression> expr;
  std::shared_ptr<Statement> stmt;
};


