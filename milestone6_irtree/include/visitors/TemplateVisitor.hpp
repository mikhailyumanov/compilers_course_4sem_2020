#pragma once

#include "utils/BasicElement.hpp"
#include "visitors/Visitor.hpp"

template<typename T>
class TemplateVisitor: public Visitor {
 public:
    virtual T Accept(std::shared_ptr<BasicElement> element) = 0;
 protected:
    T tos_value_;
};
