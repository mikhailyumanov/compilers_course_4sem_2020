#pragma once

#include <iostream>


struct Type {
  bool IsIntegral() const;

  friend std::ostream& operator<<(std::ostream& stream, const Type& type);

  std::string type;
  bool is_array;
};

