#pragma once

#include <vector>

#include "types/Object.hpp"

class Class: public Object {
 public:
  Class(const std::string& type);

  bool IsClass() const override;

  void Print(std::ostream& stream) const override;
};

