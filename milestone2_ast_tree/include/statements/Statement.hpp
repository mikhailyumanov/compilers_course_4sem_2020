#pragma once

#include "utils/BasicElement.hpp"


class Statement: virtual public BasicElement {
 public:
  virtual void Perform() const = 0;
};
