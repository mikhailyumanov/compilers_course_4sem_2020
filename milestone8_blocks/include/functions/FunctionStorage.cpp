#include <cassert>

#include "functions/FunctionStorage.hpp"


FunctionStorage& FunctionStorage::GetInstance() {
  static FunctionStorage storage;
  return storage;
}

void FunctionStorage::SetFunction(std::string class_name,
    std::string func_name, std::shared_ptr<Function> function) {
  methods_[class_name][func_name] = function;
}

std::shared_ptr<Function> FunctionStorage::GetFunction(
    std::string class_name, std::string func_name) {
  return methods_[class_name][func_name];
}

void FunctionStorage::DeclareClass(std::string class_name) {
  methods_[class_name] =
    std::unordered_map<std::string, std::shared_ptr<Function>>();
}

void FunctionStorage::DeclareFunction(std::string class_name,
    std::string func_name, FunctionType function_type) {
  methods_[class_name][func_name] = std::make_shared<Function>(function_type);
}

bool FunctionStorage::HasClass(std::string class_name) const {
  return methods_.find(class_name) != methods_.end();
}

bool FunctionStorage::HasFunction(std::string class_name, 
    std::string func_name) const {
  return HasClass(class_name) && 
    (methods_.at(class_name).find(func_name) != 
     methods_.at(class_name).end());
}
