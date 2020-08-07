#include "jouette/instructions/commands/MoveInstruction.hpp"

namespace Jouette {

template <InstructionType type>
MoveInstruction<type>::MoveInstruction(std::shared_ptr<Register> output, 
    std::shared_ptr<Register> input)
  : output{output}, input{input} {
}

template <InstructionType type>
void MoveInstruction<type>::Accept(std::shared_ptr<Jouette::Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

template class MoveInstruction<InstructionType::Movea>;
template class MoveInstruction<InstructionType::Moved>;
template class MoveInstruction<InstructionType::Movem>;

}
