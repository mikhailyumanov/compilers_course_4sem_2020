#include "jouette/instructions/commands/CJumpInstruction.hpp"

namespace Jouette {

template <InstructionType type>
CJumpInstruction<type>::CJumpInstruction(Label label, 
    std::shared_ptr<Register> input)
  : label{label}, input{input} {
}

template <InstructionType type>
void CJumpInstruction<type>::Accept(std::shared_ptr<Jouette::Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

template class CJumpInstruction<InstructionType::Bge>;
template class CJumpInstruction<InstructionType::Blt>;
template class CJumpInstruction<InstructionType::Beq>;
template class CJumpInstruction<InstructionType::Bne>;

}
