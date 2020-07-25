#pragma once

#include "types/Object.hpp"
#include "types/Bool.hpp"

class Integer: public Object {
 public:
  explicit Integer(int value);
  int ToInt() const override;
  bool ToBool() const override;

  void Print(std::ostream& stream) const override;

 private:
  int value_;
};

