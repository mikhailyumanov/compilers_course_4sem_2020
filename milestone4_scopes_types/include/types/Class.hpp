#pragma once

#include "types/Object.hpp"

class Class: public Object {
 public:
  Class() = default;
  Class(const std::string& type);
};

