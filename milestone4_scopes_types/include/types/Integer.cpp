#include "types/Integer.hpp"

Integer::Integer(int value) : Object("integer"), value_(value) {
}

int Integer::ToInt() const {
  return value_;
}

bool Integer::ToBool() const {
  return value_;
}

