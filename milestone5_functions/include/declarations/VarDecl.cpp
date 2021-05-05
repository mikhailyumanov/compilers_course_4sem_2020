#include "declarations/VarDecl.hpp"

VarDecl::VarDecl(Type type, const std::string& name)
  : type{type}, name{name} {
}

void VarDecl::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
