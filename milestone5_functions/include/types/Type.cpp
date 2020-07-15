#include "types/Type.hpp"


bool Type::IsIntegral() const {
  return type == "int" || type == "boolean";
}


std::ostream& operator<<(std::ostream& stream, const Type& type) {
  stream << "type: " << type.type << ", is array: " << type.is_array;
  return stream;
}
