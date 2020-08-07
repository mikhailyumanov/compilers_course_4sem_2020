#pragma once

#include <iostream>
#include <memory>

#include "irtree/generators/Temporary.hpp"


namespace Jouette {

class Register: public std::enable_shared_from_this<Register> {
 public:
  Register() = default;
  Register(const IRT::Temporary& temp);

  IRT::Temporary GetTemporary() const;
  bool IsNull() const;

  operator std::string() const;
  
 private:
   IRT::Temporary temp_;
};

std::ostream& operator<<(std::ostream&, const Register&);

std::shared_ptr<Register> GetNullRegister();

}
