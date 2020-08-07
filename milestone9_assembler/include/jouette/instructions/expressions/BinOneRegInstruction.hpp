#pragma once

#include "jouette/instructions/expressions/Expression.hpp"


namespace Jouette {

template <InstructionType type>
class BinOneRegInstruction: public Expression, 
  public std::enable_shared_from_this<BinOneRegInstruction<type>> {
 public:
  BinOneRegInstruction() = default;
  BinOneRegInstruction(std::shared_ptr<Register> output, 
      std::shared_ptr<Register> input, int cnst);

  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Register> input;
  int cnst = 0;
};

}
