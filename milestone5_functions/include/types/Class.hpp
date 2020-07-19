#pragma once

#include <vector>
#include <unordered_map>

#include "types/Object.hpp"
#include "scopes/Symbol.hpp"

class Class: public Object {
 public:
  Class(const std::string& type);

  void SetValue(Symbol name, std::shared_ptr<Object> value);
  std::shared_ptr<Object> GetValue(Symbol name) const;

  bool IsClass() const override;

  void Print(std::ostream& stream) const override;

 private:
  std::unordered_map<Symbol, std::shared_ptr<Object>> fields_;
};

