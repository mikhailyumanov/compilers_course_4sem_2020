#include "types/Bool.hpp"

Bool::Bool(bool value) : Object("bool"), value_(value) {
}

int Bool::ToInt() const {
  return value_;
}

bool Bool::ToBool() const {
  return value_;
}

