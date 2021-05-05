#pragma once

#include "types/constructor/Constructor.hpp"
#include "types/Class.hpp"


class ClassBuilder: std::enable_shared_from_this<ClassBuilder> {
 public:
  std::shared_ptr<Object> CreateObject(std::string class_name) const;

  void SetClassParam(std::string, Symbol, Type);
  const std::unordered_map<Symbol, Type>& GetClassParams(
      std::string class_name) const;

 private:
  static std::unordered_map<std::string, std::unordered_map<Symbol, Type>>
    recipes_;
};
