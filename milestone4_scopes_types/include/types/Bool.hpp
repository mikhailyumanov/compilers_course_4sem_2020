#pragma once

#include "types/Object.hpp"

class Bool: public Object {
 public:
  explicit Bool(bool value);
  int ToInt() const override;
  bool ToBool() const override;

 private:
  bool value_;
};

