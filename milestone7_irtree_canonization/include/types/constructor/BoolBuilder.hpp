#pragma once

#include "types/Bool.hpp"


class BoolBuilder: std::enable_shared_from_this<BoolBuilder> {
 public:
  std::shared_ptr<Object> CreateObject(bool value) const;
};
