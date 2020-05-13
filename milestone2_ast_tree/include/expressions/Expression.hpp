#pragma once

#include "utils/BasicElement.hpp"


class Expression: virtual public BasicElement {
 public:
  virtual int Eval() const = 0;
};
