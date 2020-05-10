#pragma once

#include <memory>

#include "utils/BasicElement.hpp"
#include "visitors/Visitor.hpp"


class ClassDecl: public BasicElement {
 public:
  void Accept(std::shared_ptr<Visitor> visitor);
};
