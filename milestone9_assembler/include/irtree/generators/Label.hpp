//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include <string>
#include <memory>

namespace IRT {

class Label: public std::enable_shared_from_this<Label> {
 public:
  Label();
  explicit Label(const std::string& label);

  std::string ToString() const;

 private:
  std::string label_;
  static int counter_;
};


Label& GetDoneLabel();
bool IsDoneLabel(const Label& label);

Label& GetMainLabel();
bool IsMainLabel(const Label& label);

}
