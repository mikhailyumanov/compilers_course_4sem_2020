#pragma once

#include "utils/BasicElement.hpp"


class Expression: public BasicElement {
 public:
  virtual int Eval() const = 0;
};
