#pragma once

#include <string>
#include "utils/BasicElement.hpp"
#include "scopes/VarScope.hpp"


class Decl: virtual public BasicElement {
 public:
  Type type;
  std::string name;
};
