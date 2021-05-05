#pragma once

#include "Expression.hpp"

class BinOpExpr: public Expression, 
  public std::enable_shared_from_this<BinOpExpr> {
 public:
  enum class Operation {  
    OP_AND,
    OP_OR,
    OP_LESS,
    OP_GREATER,
    OP_EQUAL,
    OP_PLUS,
    OP_MINUS,
    OP_STAR,
    OP_SLASH,
    OP_RMNDR,
  };

  BinOpExpr(std::shared_ptr<Expression> lhs,
      Operation op, std::shared_ptr<Expression> rhs);

  int Eval() const override;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Expression> lhs;
  std::shared_ptr<Expression> rhs;
  Operation op;
};
