#pragma once

#include <memory>
#include <vector>

#include "types/Object.hpp"

class Array: public Object {
 public:
  Array() = default;
  Array(std::string type, 
      const std::vector<std::shared_ptr<Object>>& array);

  int GetLength() const;
  std::shared_ptr<Object>& operator[](size_t idx);
  const std::shared_ptr<Object>& operator[](size_t idx) const;

  void Print(std::ostream& stream) const override;

 private:
  std::vector<std::shared_ptr<Object>> buffer_;
};
