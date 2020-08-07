#pragma once

#include "jouette/instructions/Instruction.hpp"


namespace Jouette {

class Expression: public Instruction { 
 public:
  Expression() = default;
  Expression(std::shared_ptr<Register> output) : output{output} {}
    
  std::shared_ptr<Register> output;
};

}
