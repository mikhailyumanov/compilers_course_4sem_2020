#include "types/constructor/BoolBuilder.hpp"

std::shared_ptr<Object> BoolBuilder::CreateObject(bool value) const {
  return std::make_shared<Bool>(value);
}
