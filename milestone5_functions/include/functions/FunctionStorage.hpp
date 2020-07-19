#pragma once

#include <memory>
#include <unordered_map>

#include "types/Function.hpp"
#include "types/FunctionType.hpp"


class FunctionStorage {
 public:
  void SetFunction(std::string class_name, std::string func_name,
      std::shared_ptr<Function> function);
  std::shared_ptr<Function> GetFunction(std::string class_name,
      std::string func_name);

  static FunctionStorage& GetInstance();

  void DeclareClass(std::string class_name);
  void DeclareFunction(std::string class_name, std::string func_name,
      FunctionType function_type);

  bool HasClass(std::string class_name) const;
  bool HasFunction(std::string class_name, std::string func_name) const;

  FunctionStorage() = default;
  FunctionStorage(const FunctionStorage&) = delete;
  FunctionStorage& operator=(const FunctionStorage&) = delete;
 ~FunctionStorage() = default;

 private:
  std::unordered_map<std::string /*class name*/, 
    std::unordered_map<std::string /*function name*/, 
      std::shared_ptr<Function> /*function*/>> methods_;
};
