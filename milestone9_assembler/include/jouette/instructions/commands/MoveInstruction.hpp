#pragma once

#include "jouette/instructions/commands/Command.hpp"


namespace Jouette {

template <InstructionType type>
class MoveInstruction: public Command,
  public std::enable_shared_from_this<MoveInstruction<type>> {
 public:
  MoveInstruction() = default;
  MoveInstruction(std::shared_ptr<Register> output, 
      std::shared_ptr<Register> input);

  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Register> output;
  std::shared_ptr<Register> input;
};

}
