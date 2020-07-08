#pragma once

#include "types/Object.hpp"

class Integer: public Object {
 public:
  explicit Integer(int value);
  int ToInt() const override;
  bool ToBool() const override;

 private:
  int value_;
};

