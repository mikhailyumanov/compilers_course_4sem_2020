//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include <vector>

#include "irtree/nodes/BaseElement.hpp"


namespace IRT {

class Expression;

class ExpressionList : public BaseElement,
 public std::enable_shared_from_this<ExpressionList> {
 public:
  ExpressionList() = default;

  void AddItem(std::shared_ptr<Expression> expression);
  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  std::vector<std::shared_ptr<Expression>> expr_list;
};

}

