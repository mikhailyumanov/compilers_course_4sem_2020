//
// Created by akhtyamovpavel on 4/14/20.
//

#pragma once

#include "irtree/generators/Temporary.hpp"
#include "functions/address/Address.hpp"


namespace IRT {

class AddressInRegister : public Address,
  public std::enable_shared_from_this<AddressInRegister> {
 public:
  AddressInRegister(const Temporary& temp);
  std::shared_ptr<Expression> ToExpression() override;

 private:
  Temporary temp_;
};

}

