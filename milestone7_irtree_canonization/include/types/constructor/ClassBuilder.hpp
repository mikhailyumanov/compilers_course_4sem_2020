#pragma once

#include "types/constructor/Constructor.hpp"
#include "types/Class.hpp"


class ClassBuilder: std::enable_shared_from_this<ClassBuilder> {
 public:
  std::shared_ptr<Object> CreateObject(std::string class_name) const;

  void SetClassField(std::string, Symbol, Type);
  const std::unordered_map<Symbol, Type>& GetClassFields(
      std::string class_name) const;

  size_t GetFieldIndex(std::string class_name, std::string field_name) const;
  size_t GetSize(std::string class_name) const;

 private:
  static std::unordered_map<std::string, std::unordered_map<Symbol, Type>>
    recipes_;
  static std::unordered_map<std::string, std::unordered_map<Symbol, size_t>> 
    field_indexes_;
  static std::unordered_map<std::string, size_t> field_counter_;
  static std::unordered_map<std::string, size_t> sizes_;
};
