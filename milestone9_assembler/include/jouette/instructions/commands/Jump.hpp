#pragma once

#include "jouette/instructions/commands/Command.hpp"
#include "jouette/instructions/commands/Label.hpp"


namespace Jouette {

class Jump: public Command,
  public std::enable_shared_from_this<Jump> {
 public:
  Jump() = default;
  Jump(Label label);

  void Accept(std::shared_ptr<Visitor> visitor) override;

  Label label;
};

}
