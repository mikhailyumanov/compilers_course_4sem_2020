//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/generators/Label.hpp"


IRT::Label::Label(): label_("L" + std::to_string(counter_++)) {
}

IRT::Label::Label(const std::string& label): label_{label} {
}

std::string IRT::Label::ToString() const {
  return label_;
}

int IRT::Label::counter_ = 0;

