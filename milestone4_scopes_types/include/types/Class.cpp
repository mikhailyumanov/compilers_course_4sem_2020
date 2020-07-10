#include "types/Class.hpp"

Class::Class(const std::string& type) : Object({type, false}) {
}

void Class::Print(std::ostream& stream) const {
  stream << "Class " << type_;
}
