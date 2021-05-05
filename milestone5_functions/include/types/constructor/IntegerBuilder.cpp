#include "types/constructor/IntegerBuilder.hpp"

std::shared_ptr<Object> IntegerBuilder::CreateObject(int value) const {
  return std::make_shared<Integer>(value);
}
