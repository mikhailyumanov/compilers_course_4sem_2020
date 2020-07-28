#pragma once

#include "expressions/Expression.hpp"
#include "utils/BasicElement.hpp"
#include "visitors/Visitor.hpp"


class Lvalue: public BasicElement,
  public std::enable_shared_from_this<Lvalue> {
 public:
  Lvalue(const std::string& name);
  Lvalue(const std::string& name, std::shared_ptr<Expression> expr);
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::string name;
  std::shared_ptr<Expression> expr;
};
