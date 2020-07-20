#pragma once

#include <memory>

#include "visitors/Visitor.hpp"
#include "parser.hh"


class BasicElement{
 public:
  virtual void Accept(std::shared_ptr<Visitor> visitor) = 0;

  void SetLocation(yy::location new_loc);
  yy::location GetLocation() const;

  virtual ~BasicElement() = default;
 
 private: 
  yy::location location;
};
