#pragma once

#include "utils/BasicElement.hpp"


class Expression: virtual public BasicElement {
 public:
  virtual int Eval() const = 0;

  Type GetType() const {
    return type_;
  }

  void SetType(Type type) {
    type_ = type;
  }
  
 protected:
  Type type_;
};
