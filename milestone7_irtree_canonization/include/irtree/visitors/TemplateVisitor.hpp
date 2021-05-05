//
// Created by akhtyamovpavel on 4/15/20.
//

#pragma once

#include "irtree/visitors/Visitor.hpp"
#include "irtree/nodes/BaseElement.hpp"


namespace IRT {

template<typename T>
class TemplateVisitor : public Visitor {
 public:
  virtual T Accept(std::shared_ptr<BaseElement> element) = 0;

 protected:
  T tos_value_;
};

}


