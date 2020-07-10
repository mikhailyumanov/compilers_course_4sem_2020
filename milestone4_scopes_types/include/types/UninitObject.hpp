#pragma once

#include "types/Object.hpp"

class UninitObject: public Object {
 public:
  UninitObject(Type type);

  int ToInt() const override;
  bool ToBool() const override;
};
