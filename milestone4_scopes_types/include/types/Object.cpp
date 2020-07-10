#include "types/Object.hpp"


Object::Object(Type type) : type_{type} {
}

int Object::ToInt() const {
  return 0;
}

bool Object::ToBool() const {
  return false;
}

Type Object::GetType() const {
  return type_;
}

std::string Object::GetTypeName() const {
  return type_.type;
}

bool Object::IsArray() const {
  return type_.is_array;
}

void Object::SetArray(bool is_array) {
  type_.is_array = is_array;
}

void Object::Print(std::ostream& stream) const {
  stream << "Object";
}
