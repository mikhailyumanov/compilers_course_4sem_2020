//
// Created by akhtyamovpavel on 4/14/20.
//

#include "functions/address/AddressInRegister.hpp"
#include "functions/address/AddressInFrame.hpp"
#include "functions/FrameTranslator.hpp"
#include "irtree/nodes/expressions/ConstExpression.hpp"

namespace IRT {

FrameTranslator::FrameTranslator(const std::string& function_name)
  : function_name_(function_name) {
  addresses_[frame_pointer_address_].push(
      std::make_shared<AddressInRegister>(
        Temporary(frame_pointer_address_)));

  addresses_[return_value_address_].push(
      std::make_shared<AddressInRegister>(
        Temporary(return_value_address_)));
}

void FrameTranslator::SetupScope() {
  symbols_.push("{");
}

void FrameTranslator::TearDownScope() {
  while (symbols_.top() != "{") {
    std::string symbol = symbols_.top();

//    std::cerr << "Popping " << symbol.GetName() << std::endl;

    addresses_[symbol].pop();
    if (addresses_[symbol].empty()) {
      addresses_.erase(symbol);
    }
    symbols_.pop();
  }
  symbols_.pop();
}

void FrameTranslator::AddVariable(const std::string &name) {
  symbols_.push(name);
  addresses_[name].push(
      std::make_shared<AddressInFrame>(FramePointer(),
        std::make_shared<IRT::ConstExpression>(GetOffset())
  ));
}

void FrameTranslator::AddLocalVariable(const std::string &name) {
  AddVariable(name);
}

void FrameTranslator::AddReturnAddress() {
  AddVariable(return_address_);
}

void FrameTranslator::AddThisAddress() {
  AddVariable(this_address_);
}

void FrameTranslator::AddArgumentAddress(const std::string &name) {
  AddVariable(name);
}

std::shared_ptr<Address> FrameTranslator::FramePointer() {
  return addresses_[frame_pointer_address_].top();
}

std::shared_ptr<Address> FrameTranslator::GetAddress(const std::string &name) {
  return addresses_[name].top();
}

std::shared_ptr<Address> FrameTranslator::GetReturnValueAddress() {
  return GetAddress(return_value_address_);
}

std::shared_ptr<Address> FrameTranslator::GetThisAddress() {
  return GetAddress(this_address_);
}

int FrameTranslator::GetOffset() {
  int tmp = max_offset_;
  max_offset_ += word_size_;
  return tmp;
}

}
