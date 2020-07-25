#include "expressions/BinOpExpr.hpp"

BinOpExpr::BinOpExpr(std::shared_ptr<Expression> lhs,
    Operation op, std::shared_ptr<Expression> rhs)
  : lhs{lhs}, op{op}, rhs{rhs} {
}

int BinOpExpr::Eval() const {
  int tmp = 0;

  switch(op) {
    case Operation::OP_AND:     tmp = lhs->Eval() && rhs->Eval(); break;
    case Operation::OP_OR:      tmp = lhs->Eval() || rhs->Eval(); break;
    case Operation::OP_LESS:    tmp = lhs->Eval() <  rhs->Eval(); break;
    case Operation::OP_GREATER: tmp = lhs->Eval() >  rhs->Eval(); break;
    case Operation::OP_EQUAL:   tmp = lhs->Eval() == rhs->Eval(); break;
    case Operation::OP_PLUS:    tmp = lhs->Eval() +  rhs->Eval(); break;
    case Operation::OP_MINUS:   tmp = lhs->Eval() -  rhs->Eval(); break;
    case Operation::OP_STAR:    tmp = lhs->Eval() *  rhs->Eval(); break;
    case Operation::OP_SLASH:   tmp = lhs->Eval() /  rhs->Eval(); break;
    case Operation::OP_RMNDR:   tmp = lhs->Eval() %  rhs->Eval(); break;
    default: break;
  }
    return tmp;
}

void BinOpExpr::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
