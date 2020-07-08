#include "types/Array.hpp"


Array::Array(const std::vector<std::shared_ptr<Object>>& array)
  : buffer_(array) {
}

int Array::GetLength() const {
  return buffer_.size();
}

Object& Array::operator[](size_t idx) {
  return *buffer_[idx];
}

const Object& Array::operator[](size_t idx) const {
  return *buffer_[idx];
}
