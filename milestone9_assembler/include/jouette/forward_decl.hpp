#pragma once

#include "typing.hpp"


namespace Jouette {

class Instruction;

template <InstructionType> class BinTwoRegInstruction;
using Add = BinTwoRegInstruction<InstructionType::Add>;
using Sub = BinTwoRegInstruction<InstructionType::Sub>;
using Mul = BinTwoRegInstruction<InstructionType::Mul>;
using Div = BinTwoRegInstruction<InstructionType::Div>;

template <InstructionType> class BinOneRegInstruction;
using Addi = BinOneRegInstruction<InstructionType::Addi>;
using Subi = BinOneRegInstruction<InstructionType::Subi>;

template <InstructionType> class MoveInstruction;
using Movea = MoveInstruction<InstructionType::Movea>;
using Moved = MoveInstruction<InstructionType::Moved>;

class Load;
class Store;
using Movem = MoveInstruction<InstructionType::Movem>;

class Call;
class Return;

class Label;

template <InstructionType> class CJumpInstruction;
using Bge = CJumpInstruction<InstructionType::Bge>;
using Blt = CJumpInstruction<InstructionType::Blt>;
using Beq = CJumpInstruction<InstructionType::Beq>;
using Bne = CJumpInstruction<InstructionType::Bne>;

class Jump;

}
