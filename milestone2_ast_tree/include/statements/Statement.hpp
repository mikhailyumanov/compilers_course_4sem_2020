#pragma once

#include "utils/BasicElement.hpp"


class Statement: public BasicElement {
 public:
  virtual void Perform() const = 0;
};
