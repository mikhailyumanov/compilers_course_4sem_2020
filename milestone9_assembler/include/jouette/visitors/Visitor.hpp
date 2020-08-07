#pragma once

#include <memory>

#include "debug.h"

#include "jouette/forward_decl.hpp"


namespace Jouette {

class Visitor {
 public:
  virtual void Visit(std::shared_ptr<Add> element) = 0;
  virtual void Visit(std::shared_ptr<Sub> element) = 0;
  virtual void Visit(std::shared_ptr<Mul> element) = 0;
  virtual void Visit(std::shared_ptr<Div> element) = 0;

  virtual void Visit(std::shared_ptr<Addi> element) = 0;
  virtual void Visit(std::shared_ptr<Subi> element) = 0;

  virtual void Visit(std::shared_ptr<Movea> element) = 0;
  virtual void Visit(std::shared_ptr<Moved> element) = 0;

  virtual void Visit(std::shared_ptr<Load> element) = 0;
  virtual void Visit(std::shared_ptr<Store> element) = 0;
  virtual void Visit(std::shared_ptr<Movem> element) = 0;

  virtual void Visit(std::shared_ptr<Call> element) = 0;
  virtual void Visit(std::shared_ptr<Return> element) = 0;

  virtual void Visit(std::shared_ptr<Bge> element) = 0;
  virtual void Visit(std::shared_ptr<Blt> element) = 0;
  virtual void Visit(std::shared_ptr<Beq> element) = 0;
  virtual void Visit(std::shared_ptr<Bne> element) = 0;
  virtual void Visit(std::shared_ptr<Jump> element) = 0;
  
  virtual void Visit(std::shared_ptr<Label> element) = 0;

  virtual ~Visitor() = default;
};

}
