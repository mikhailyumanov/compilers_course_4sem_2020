#pragma once

#include "types/Object.hpp"
#include "types/Integer.hpp"


class Bool: public Object {
 public:
  explicit Bool(bool value);
  int ToInt() const override;
  bool ToBool() const override;
  operator Integer() const;
  Bool operator!() const;

  void Print(std::ostream& stream) const override;

 private:
  bool value_;
};

