//
// Created by akhtyamovpavel on 4/7/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/nodes/expressions/Expression.hpp"


namespace IRT {

class ConstExpression: public Expression,
 public std::enable_shared_from_this<ConstExpression> {
 public:
  explicit ConstExpression(int value);

  int GetValue() const;
  void Accept(std::shared_ptr<Visitor> visitor) override;

  ~ConstExpression() final = default;

 private:
  int value_;
};

}

