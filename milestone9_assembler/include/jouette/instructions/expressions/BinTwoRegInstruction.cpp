#include "jouette/instructions/expressions/BinTwoRegInstruction.hpp"


namespace Jouette {

template <InstructionType type>
BinTwoRegInstruction<type>::BinTwoRegInstruction(
    std::shared_ptr<Register> output, std::shared_ptr<Register> lhs,
    std::shared_ptr<Register> rhs)
  : Expression{output}, lhs{lhs}, rhs{rhs} {
}

template <InstructionType type>
void BinTwoRegInstruction<type>::Accept(
    std::shared_ptr<Jouette::Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

template class BinTwoRegInstruction<InstructionType::Add>;
template class BinTwoRegInstruction<InstructionType::Sub>;
template class BinTwoRegInstruction<InstructionType::Mul>;
template class BinTwoRegInstruction<InstructionType::Div>;

}
