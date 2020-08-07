#pragma once

#include "jouette/instructions/expressions/Expression.hpp"


namespace Jouette {

template <InstructionType type>
class BinTwoRegInstruction: public Expression, 
  public std::enable_shared_from_this<BinTwoRegInstruction<type>> {
 public:
  BinTwoRegInstruction() = default;
  BinTwoRegInstruction(std::shared_ptr<Register> output,
      std::shared_ptr<Register> lhs, std::shared_ptr<Register> rhs);

  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Register> lhs;
  std::shared_ptr<Register> rhs;
};

}
