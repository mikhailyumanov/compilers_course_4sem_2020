#pragma once


namespace Jouette {

enum class InstructionType {
  Add,
  Sub,
  Mul,
  Div,

  Addi,
  Subi,

  Movea,
  Moved,

  Load,
  Store,
  Movem,

  Bge,
  Blt,
  Beq,
  Bne,
  Jump
};

}
