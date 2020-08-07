#pragma once

#include "jouette/instructions/commands/Command.hpp"


namespace Jouette {

class Return: public Command, public std::enable_shared_from_this<Return> {
 public:
  Return();

  void Accept(std::shared_ptr<Visitor> visitor) override;
};

}
