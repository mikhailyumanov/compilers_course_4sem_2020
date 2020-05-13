#pragma once

#include "utils/BasicElement.hpp"
#include "visitors/Visitor.hpp"


class Lvalue: public BasicElement,
  public std::enable_shared_from_this<Lvalue> {
 public:
  Lvalue(const std::string& name, bool is_array);
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::string name;
  bool is_array;
};
