#pragma once

#include <vector>

#include "jouette/instructions/expressions/Expression.hpp"
#include "jouette/instructions/commands/Label.hpp"


namespace Jouette {

class Call: public Expression, 
  public std::enable_shared_from_this<Call> {
 public:
  Call() = default;
  Call(std::shared_ptr<Register> output, Label label, 
      std::vector<std::shared_ptr<Register>> args);

  void Accept(std::shared_ptr<Visitor> visitor) override;

  Label label;
  std::shared_ptr<Register> rhs;
  std::vector<std::shared_ptr<Register>> args;
};

}
