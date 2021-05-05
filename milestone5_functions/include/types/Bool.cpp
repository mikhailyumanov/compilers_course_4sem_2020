#include "types/Bool.hpp"

Bool::Bool(bool value) : Object({"bool", false}), value_(value) {
}

int Bool::ToInt() const {
  return value_;
}

bool Bool::ToBool() const {
  return value_;
}

Bool::operator Integer() const {
  return Integer(ToInt());
}

Bool Bool::operator!() const {
  return Bool(!value_);
}

void Bool::Print(std::ostream& stream) const {
  stream << value_;
}
