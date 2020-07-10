#include "types/Integer.hpp"

Integer::Integer(int value) : Object({"integer", false}), value_(value) {
}

int Integer::ToInt() const {
  return value_;
}

bool Integer::ToBool() const {
  return value_;
}

void Integer::Print(std::ostream& stream) const {
  stream << value_;
}
