#pragma once


#include "jouette/visitors/Visitor.hpp"
#include "jouette/registers/Register.hpp"


namespace Jouette {

class Instruction {
 public:
  virtual ~Instruction() = default;

  virtual void Accept(std::shared_ptr<Visitor> visitor) = 0;
};

}
