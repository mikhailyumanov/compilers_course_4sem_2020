//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//


#pragma once

#include "irtree/nodes/expressions/Expression.hpp"
#include "irtree/generators/Label.hpp"


namespace IRT {
class NameExpression : public Expression,
 public std::enable_shared_from_this<NameExpression> {
 public:
  NameExpression(Label label);

  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  Label label;
};

}


