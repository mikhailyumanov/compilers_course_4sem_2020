#include "value_categories/Lvalue.hpp"


Lvalue::Lvalue(const std::string& name, std::shared_ptr<Expression> expr)
  : name{name}, expr{expr} {
}

Lvalue::Lvalue(const std::string& name) : Lvalue(name, nullptr){
}

void Lvalue::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
