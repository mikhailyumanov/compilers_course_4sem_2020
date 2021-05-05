#include "types/constructor/Constructor.hpp"

Constructor& Constructor::GetInstance() {
  DEBUG_SINGLE("Constructor::GetInstance")

  static Constructor constructor;
  return constructor;
}

std::shared_ptr<Object> Constructor::Construct(std::string type) const {
  DEBUG_SINGLE("Constructor::Construct")

  std::shared_ptr<Object> object;
  if (type == "int") {
    object = std::make_shared<IntegerBuilder>()->CreateObject(0);
  } else if (type == "boolean") {
    object = std::make_shared<BoolBuilder>()->CreateObject(false);
  } else {
    object = std::make_shared<ClassBuilder>()->CreateObject(type);
  }

  return object;
}
