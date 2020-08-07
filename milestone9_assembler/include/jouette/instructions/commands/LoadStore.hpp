#pragma once

#include "jouette/instructions/commands/Command.hpp"


namespace Jouette {

class Load: public Command,
  public std::enable_shared_from_this<Load> {
 public:
  Load() = default;
  Load(std::shared_ptr<Register> output, 
       std::shared_ptr<Register> input, int cnst);

  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Register> output;
  std::shared_ptr<Register> input;
  int cnst = 0;
};


class Store: public Command,
  public std::enable_shared_from_this<Store> {
 public:
  Store() = default;
  Store(std::shared_ptr<Register> output, int cnst, 
        std::shared_ptr<Register> input);

  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::shared_ptr<Register> output;
  int cnst = 0;
  std::shared_ptr<Register> input;
};

}
