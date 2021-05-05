#include "types/Type.hpp"


bool Type::IsIntegral() const {
  return type == "int" || type == "boolean";
}

bool Type::IsClass() const {
  return !(IsIntegral() || type == "void");
}

std::string Type::ToString() const {
  return "type: " + type + ", is_array: " + (is_array ? "true" : "false");
}

std::ostream& operator<<(std::ostream& stream, const Type& type) {
  stream << type.ToString();
  return stream;
}

bool Type::operator==(const Type& other) const {
 return type == other.type && is_array == other.is_array;
}

bool Type::operator!=(const Type& other) const {
  return !(*this == other);
}
