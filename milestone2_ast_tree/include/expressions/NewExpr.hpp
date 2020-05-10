#pragma once

#include <memory>
#include <string>

#include "expressions/Expression.hpp"


class NewExpr: public Expression,
  public std::enable_shared_from_this<NewExpr> { 
 public:
  NewExpr(const std::string& type);
  
  int Eval() const override;

 private:
  std::string type_;
};
