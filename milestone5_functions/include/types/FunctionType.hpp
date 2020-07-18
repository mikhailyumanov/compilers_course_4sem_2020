#pragma once

#include <vector>

#include "types/Type.hpp"


struct FunctionType: public Type {
  FunctionType(Type return_type, const std::vector<Type>& arg_types,
      const std::vector<std::string>& arg_names);
  FunctionType() = default;

  size_t GetNumArgs() const;
  bool IsMain() const;

  friend std::ostream& operator<<(std::ostream& stream,
      const FunctionType& type);

  std::vector<Type> arg_types;
  std::vector<std::string> arg_names;
  bool is_main = false;
};
