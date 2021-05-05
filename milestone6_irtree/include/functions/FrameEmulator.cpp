#include "functions/FrameEmulator.hpp"


FrameEmulator::FrameEmulator(FunctionType function_type) {
  // do not forget about *this (+1)
  args_.resize(function_type.GetNumArgs() + 1);
  AllocScope();
}



std::shared_ptr<Object> FrameEmulator::GetValue(int idx) const {
  if (idx >= 0) {
    return vars_.at(idx);
  } else {
    // again, do not forget: args_[0] = *this
    return args_.at(-idx - 1);
  }
}

void FrameEmulator::SetValue(int idx, std::shared_ptr<Object> value) {
  if (idx >= 0) {
    vars_.at(idx) = value;
  } else {
    // again, do not forget: args_[0] = *this
    args_.at(-idx - 1) = value;
  }
}

void FrameEmulator::SetArgs(const std::vector<std::shared_ptr<Object>>& args) {
  if (args.size() != args_.size()) {
    throw std::runtime_error("Wrong number of parameters: " +
        std::to_string(args.size())  + "; " + 
        std::to_string(args_.size()) + "expected.");
  }

  args_ = args;
}



std::shared_ptr<FrameEmulator> FrameEmulator::GetParent() const {
  return parent_;
}

void FrameEmulator::SetParent(std::shared_ptr<FrameEmulator> parent) {
  parent_ = parent;
}

void FrameEmulator::SetParentReturnValue(std::shared_ptr<Object> value) const {
  parent_->return_value_ = value;
}

bool FrameEmulator::HasParent() const {
  return (bool) parent_;
}



void FrameEmulator::SetReturned() {
  returned_ = true;
}

bool FrameEmulator::IsReturned() const {
  return returned_;
}



std::shared_ptr<Object> FrameEmulator::GetReturnValue() const {
  return return_value_;
}



size_t FrameEmulator::AllocVariable() {
  vars_.push_back(std::make_shared<UninitObject>(Type{"empty", false}));
  return vars_.size() - 1;
}

void FrameEmulator::AllocScope() {
  offsets_.push(vars_.size());
}

void FrameEmulator::DeallocScope() {
  vars_.resize(offsets_.top());
  offsets_.pop();
}



void FrameEmulator::SetReturnValue(std::shared_ptr<Object> value) {
  return_value_ = value;
}
