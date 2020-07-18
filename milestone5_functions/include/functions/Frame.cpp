#include "functions/Frame.hpp"


Frame::Frame(FunctionType function_type) {
  // do not forget about *this (+1)
  args_.resize(function_type.GetNumArgs() + 1);
  AllocScope();
}

std::shared_ptr<Object> Frame::GetValue(size_t idx) const {
  if (idx >= 0) {
    return vars_.at(idx);
  } else {
    // again, do not forget: args_[0] = *this
    return args_.at(-idx);
  }
}

void Frame::SetValue(size_t idx, std::shared_ptr<Object> value) {
  if (idx >= 0) {
    vars_.at(idx) = value;
  } else {
    // again, do not forget: args_[0] = *this
    args_.at(-idx) = value;
  }
}

void Frame::SetParent(std::shared_ptr<Frame> parent) {
  parent_ = parent;
}

void Frame::SetParentReturnValue(std::shared_ptr<Object> value) const {
  parent_->return_value_ = value;
}

std::shared_ptr<Object> Frame::GetReturnValue() const {
  return return_value_;
}

size_t Frame::AllocVariable() {
  vars_.push_back(std::make_shared<UninitObject>(Type{"empty", false}));
  return vars_.size() - 1;
}

void Frame::AllocScope() {
  offsets_.push(vars_.size());
}

void Frame::DeallocScope() {
  vars_.resize(offsets_.top());
  offsets_.pop();
}

void Frame::SetReturnValue(std::shared_ptr<Object> value) {
  return_value_ = value;
}
