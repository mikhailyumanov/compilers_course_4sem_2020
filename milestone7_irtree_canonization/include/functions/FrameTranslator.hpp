//
// Created by akhtyamovpavel on 4/14/20.
//

#pragma once

#include <string>
#include <unordered_map>
#include <stack>
#include <vector>

#include "functions/address/Address.hpp"


namespace IRT {

class FrameTranslator: public std::enable_shared_from_this<FrameTranslator> {
 public:
  FrameTranslator(const std::string& function_name);
  void SetupScope();
  void TearDownScope();

  void AddVariable(const std::string& name);
  void AddLocalVariable(const std::string& name);
  void AddReturnAddress();
  void AddThisAddress();

  void AddArgumentAddress(const std::string& name);

  std::shared_ptr<Address> FramePointer();
  std::shared_ptr<Address> GetAddress(const std::string& name);
  std::shared_ptr<Address> GetReturnValueAddress();
  std::shared_ptr<Address> GetThisAddress();

 private:
  int GetOffset();

 private:
  std::string return_address_ = "::return";
  std::string frame_pointer_address_ = "::fp";
  std::string return_value_address_ = "::return_value";
  std::string this_address_ = "::this";

  std::unordered_map<std::string, std::stack<std::shared_ptr<Address>>> 
    addresses_;

  std::stack<std::string> symbols_;
  int word_size_ = 4;
  std::string function_name_;

  int max_offset_ = 0;
};

}

