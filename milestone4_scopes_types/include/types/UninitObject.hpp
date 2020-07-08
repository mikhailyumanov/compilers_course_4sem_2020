#pragma once

#include "types/Object.hpp"

class UninitObject: public Object {
 public:
  int ToInt() const override;
  bool ToBool() const override;
};
