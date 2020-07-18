#pragma once

#include "types/Object.hpp"

#include <iterator>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>


class Frame: public std::enable_shared_from_this<Frame> {
 public:
  explicit Frame(FunctionType function_type);

  std::shared_ptr<Object> GetValue(size_t idx) const;
  void SetValue(size_t idx, std::shared_ptr<Object> value);

  void SetParent(std::shared_ptr<Frame> parent);
  void SetParentReturnValue(std::shared_ptr<Object> value) const;

  std::shared_ptr<Object> GetReturnValue() const;

  size_t AllocVariable();
  void AllocScope();
  void DeallocScope();

 private:
  void SetReturnValue(std::shared_ptr<Object> value);

 private:
  std::shared_ptr<Frame> parent_;
  std::shared_ptr<Object> return_value_;
  std::stack<size_t> offsets_;
  std::vector<std::shared_ptr<Object>> args_;
  std::vector<std::shared_ptr<Object>> vars_;
};

