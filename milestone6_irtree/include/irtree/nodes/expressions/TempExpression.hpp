//
// Created by akhtyamovpavel on 4/10/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/nodes/expressions/Expression.hpp"
#include "irtree/generators/Temporary.hpp"


namespace IRT {

class TempExpression: public Expression,
 public std::enable_shared_from_this<TempExpression> {
 public:
  explicit TempExpression(const IRT::Temporary& temporary);

  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  Temporary temporary;
};

}


