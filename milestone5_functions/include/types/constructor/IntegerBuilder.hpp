#pragma once

#include "types/Integer.hpp"


class IntegerBuilder: std::enable_shared_from_this<IntegerBuilder> {
 public:
  std::shared_ptr<Object> CreateObject(int value) const;
};
