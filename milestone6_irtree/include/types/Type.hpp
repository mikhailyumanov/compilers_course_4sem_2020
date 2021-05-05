#pragma once

#include <iostream>

#include "debug.h"


struct Type {
  bool IsIntegral() const;
  bool IsClass() const;

  friend std::ostream& operator<<(std::ostream& stream, const Type& type);
  std::string ToString() const;

  bool operator==(const Type& other) const;
  bool operator!=(const Type& other) const;

  std::string type;
  bool is_array;
};

