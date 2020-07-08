#pragma once

#include <string>
#include "utils/BasicElement.hpp"


class Decl: virtual public BasicElement {
 public:
  Type type;
  std::string name;
};
