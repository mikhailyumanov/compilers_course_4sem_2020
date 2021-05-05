#pragma once

#include "types/Object.hpp"

class Class: public Object {
 public:
  Class(const std::string& type);

  void Print(std::ostream& stream) const override;
};

