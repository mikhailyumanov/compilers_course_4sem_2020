#include "types/constructor/ClassBuilder.hpp"

std::unordered_map<std::string, std::unordered_map<Symbol, Type>>
  ClassBuilder::recipes_;

std::shared_ptr<Object> ClassBuilder::CreateObject(
    std::string class_name) const {
  auto& constructor = Constructor::GetInstance();
  auto new_object = std::make_shared<Class>(class_name);

  for (auto&& field : recipes_[class_name]) {
    DEBUG_SINGLE("ClassBuilder::CreateObject: " + field.first.GetName())
  }

  for (auto&& field : recipes_[class_name]) {
    new_object->SetValue(field.first, constructor.Construct(field.second.type));
  }

  return new_object;
}

void ClassBuilder::SetClassParam(std::string class_name, Symbol symbol,
    Type type) {
  if (recipes_.find(class_name) == recipes_.end()) {
    recipes_[class_name] = std::unordered_map<Symbol, Type>();
  }

  recipes_[class_name][symbol] = type;
}

const std::unordered_map<Symbol, Type>& ClassBuilder::GetClassParams(
    std::string class_name) const {
  return recipes_[class_name];
}
