#pragma once

#include "jouette/instructions/commands/Command.hpp"
#include "jouette/instructions/commands/Label.hpp"


namespace Jouette {

template <InstructionType type>
class CJumpInstruction: public Command,
  public std::enable_shared_from_this<CJumpInstruction<type>> {
 public:
  CJumpInstruction() = default;
  CJumpInstruction(Label label, std::shared_ptr<Register> input);

  void Accept(std::shared_ptr<Visitor> visitor) override;

  Label label;
  std::shared_ptr<Register> input;
};

}
