//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include <string>
#include <memory>


namespace IRT {

class Temporary: public std::enable_shared_from_this<Temporary> {
 public:
  Temporary();
  explicit Temporary(const std::string& name);
  std::string ToString() const;

 private:
  std::string name_;
  static int counter_;
};

}

