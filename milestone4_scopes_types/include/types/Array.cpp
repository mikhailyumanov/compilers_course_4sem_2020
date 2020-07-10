#include "types/Array.hpp"


Array::Array(
    std::string type, 
    const std::vector<std::shared_ptr<Object>>& array)
  : Object({type, true}), buffer_(std::move(array)) {
}

int Array::GetLength() const {
  return buffer_.size();
}

std::shared_ptr<Object>& Array::operator[](size_t idx) {
  return buffer_[idx];
}

const std::shared_ptr<Object>& Array::operator[](size_t idx) const {
  return buffer_[idx];
}

void Array::Print(std::ostream& stream) const {
  stream << "Array [ ";
  for (auto&& element : buffer_) {
    if (element) {
      element->Print(stream);
      stream << " ";
    } else {
      stream << "nullptr" << " ";
    }
  }
  stream << "] " << buffer_.size() << " elements." << std::endl;
}
