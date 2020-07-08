#include "types/Object.hpp"


Object::Object(const std::string& type) : type_{type} {
}

int Object::ToInt() const {
  return 0;
}

bool Object::ToBool() const {
  return false;
}

bool Object::IsArray() const {
  return is_array_;
}

void Object::SetArray(bool is_array) {
  is_array_ = is_array;
}

