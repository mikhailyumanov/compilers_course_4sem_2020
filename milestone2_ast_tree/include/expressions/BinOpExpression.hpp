#pragma once
#include "Expression.hpp"

using result_t = std::pair<std::vector<int>, int>;

struct BinOpExpression : Expression {
 public:
  BinOpExpression(Expression* lhs, int op, Expression* rhs)
  : lhs_{lhs}, op_{op}, rhs_{rhs} {}

  result_t eval() {
    int tmp = 0;
/*
    switch($2) {
      case token::TOK_AND:     tmp = $1.first[0] && $3.first[0]; break;
      case token::TOK_OR:      tmp = $1.first[0] || $3.first[0]; break;
      case token::TOK_LESS:    tmp = $1.first[0] <  $3.first[0]; break;
      case token::TOK_GREATER: tmp = $1.first[0] >  $3.first[0]; break;
      case token::TOK_EQUAL:   tmp = $1.first[0] == $3.first[0]; break;
      case token::TOK_PLUS:    tmp = $1.first[0] +  $3.first[0]; break;
      case token::TOK_MINUS:   tmp = $1.first[0] -  $3.first[0]; break;
      case token::TOK_STAR:    tmp = $1.first[0] *  $3.first[0]; break;
      case token::TOK_SLASH:   tmp = $1.first[0] /  $3.first[0]; break;
      case token::TOK_RMNDR:   tmp = $1.first[0] %  $3.first[0]; break;
      default: break;
    }
    */
    return std::make_pair(std::vector<int>{tmp}, 0);
  }

 private:
  Expression* lhs_;
  Expression* rhs_;
  int op_;
};
