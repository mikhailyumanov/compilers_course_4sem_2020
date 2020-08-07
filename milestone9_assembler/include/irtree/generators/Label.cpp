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

IRT::Label& IRT::GetDoneLabel() {
  static Label done_label{"%done"};
  return done_label;
}

bool IRT::IsDoneLabel(const IRT::Label& label) {
  return IRT::GetDoneLabel().ToString() == label.ToString();
}

IRT::Label& IRT::GetMainLabel() {
  static Label main_label{"%main"};
  return main_label;
}

bool IRT::IsMainLabel(const IRT::Label& label) {
  return IRT::GetMainLabel().ToString() == label.ToString();
}
