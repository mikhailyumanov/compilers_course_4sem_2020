#include "types/FunctionType.hpp"

#include <cassert>


FunctionType::FunctionType(Type return_type, 
    const std::vector<Type>& arg_types, 
    const std::vector<std::string>& arg_names)
  : Type(return_type), arg_types{arg_types}, arg_names{arg_names} {
  assert(arg_types.size() == arg_names.size());
}

size_t FunctionType::GetNumArgs() const {
  return arg_types.size();
}

bool FunctionType::IsMain() const {
  return is_main;
}

std::ostream& operator<<(std::ostream& stream, const FunctionType& type) {
  stream << "Return type: " << type.type << "; ";
  stream << "Args: ";
  for (size_t i = 0; i < type.arg_names.size(); ++i) {
    stream << type.arg_names[i] << "(" << type.arg_types[i] << "), ";
  }

  // Fun fact: replace `return stream;` with `stream << "";` - and it works
  // (sometimes)
  return stream;  
}

