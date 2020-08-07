#include "jouette/instructions/expressions/BinOneRegInstruction.hpp"


namespace Jouette {

template <InstructionType type>
BinOneRegInstruction<type>::BinOneRegInstruction(
    std::shared_ptr<Register> output, 
    std::shared_ptr<Register> input, int cnst)
  : Expression{output}, input{input}, cnst{cnst} {
}

template <InstructionType type>
void BinOneRegInstruction<type>::Accept(
    std::shared_ptr<Jouette::Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

template class BinOneRegInstruction<InstructionType::Addi>;
template class BinOneRegInstruction<InstructionType::Subi>;

}
