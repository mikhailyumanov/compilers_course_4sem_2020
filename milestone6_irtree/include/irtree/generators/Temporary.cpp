//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/generators/Temporary.hpp"


IRT::Temporary::Temporary(): name_("%" + std::to_string(counter_++)) {
}

IRT::Temporary::Temporary(const std::string &name): name_(name) {
}

std::string IRT::Temporary::ToString() const {
  return name_;
}

int IRT::Temporary::counter_ = 0;

