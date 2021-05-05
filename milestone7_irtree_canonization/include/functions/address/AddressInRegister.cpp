//
// Created by akhtyamovpavel on 4/14/20.
//

#include "functions/address/AddressInRegister.hpp"
#include "irtree/nodes/expressions/TempExpression.hpp"

namespace IRT {

AddressInRegister::AddressInRegister(const Temporary &temp)
  : temp_(temp) {
}

std::shared_ptr<Expression> AddressInRegister::ToExpression() {
  return std::make_shared<TempExpression>(temp_);
}

}
