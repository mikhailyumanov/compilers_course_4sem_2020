#include "statements/ConditionalStmt.hpp"

IfStmt::IfStmt(std::shared_ptr<Expression> expr,
    std::shared_ptr<Statement> stmt) : expr{expr}, stmt{stmt} {
}

void IfStmt::Perform() const {
  if (expr->Eval()) { stmt->Perform(); }
}

void IfStmt::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}


IfElseStmt::IfElseStmt(std::shared_ptr<Expression> expr,
    std::shared_ptr<Statement> stmt_true, 
    std::shared_ptr<Statement> stmt_false)
  : expr{expr}, stmt_true{stmt_true}, stmt_false{stmt_false} {
}

void IfElseStmt::Perform() const {
  if (expr->Eval()) { stmt_true->Perform(); } else { stmt_false->Perform(); }
}

void IfElseStmt::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}


WhileStmt::WhileStmt(std::shared_ptr<Expression> expr,
    std::shared_ptr<Statement> stmt) : expr{expr}, stmt{stmt} {
}

void WhileStmt::Perform() const {
  while (expr->Eval()) { stmt->Perform(); }
}

void WhileStmt::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
