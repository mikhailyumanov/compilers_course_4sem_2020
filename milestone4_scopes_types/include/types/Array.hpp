#pragma once

#include <memory>
#include <vector>

#include "types/Object.hpp"

class Array: public Object {
 public:
  Array() = default;
  Array(const std::vector<std::shared_ptr<Object>>& array);

  int GetLength() const;
  Object& operator[](size_t idx);
  const Object& operator[](size_t idx) const;

 private:
  std::vector<std::shared_ptr<Object>> buffer_;
};
