#include "types/constructor/ClassBuilder.hpp"

std::unordered_map<std::string, std::unordered_map<Symbol, Type>>
  ClassBuilder::recipes_;
std::unordered_map<std::string, std::unordered_map<Symbol, size_t>>
  ClassBuilder::field_indexes_;
std::unordered_map<std::string, size_t> ClassBuilder::field_counter_;
std::unordered_map<std::string, size_t> ClassBuilder::sizes_;

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

void ClassBuilder::SetClassField(std::string class_name, Symbol symbol,
    Type type) {
  if (recipes_.find(class_name) == recipes_.end()) {
    recipes_[class_name] = std::unordered_map<Symbol, Type>();
    field_indexes_[class_name] = std::unordered_map<Symbol, size_t>();
    field_counter_[class_name] = 0;
  }

  recipes_[class_name][symbol] = type;
  field_indexes_[class_name][symbol.GetName()] = field_counter_[class_name]++;
}

const std::unordered_map<Symbol, Type>& ClassBuilder::GetClassFields(
    std::string class_name) const {
  return recipes_[class_name];
}

size_t ClassBuilder::GetFieldIndex(std::string class_name, 
    std::string field_name) const {
  return field_indexes_[class_name][field_name];
}


size_t ClassBuilder::GetSize(std::string class_name) const {
  if (field_counter_[class_name] == 0) {
    return 1;
  }

  if (sizes_.find(class_name) == sizes_.end()) {
    sizes_[class_name] = 0;
    for (auto&& pair : recipes_[class_name]) {
      if (pair.second.IsIntegral()) {
        sizes_[class_name] += 4 /*word_size*/; 
      } else {
        sizes_[class_name] += GetSize(class_name);
      }
    }
  }

  return sizes_[class_name];
}
