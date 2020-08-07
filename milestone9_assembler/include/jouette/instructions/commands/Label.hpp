#pragma once

#include "jouette/instructions/commands/Command.hpp"
#include "irtree/generators/Label.hpp"


namespace Jouette {

class Label: public Command, public std::enable_shared_from_this<Label> {
 public:
  Label() = default;
  Label(IRT::Label label);

  void Accept(std::shared_ptr<Visitor> visitor) override;

  operator std::string() const;

 private:
  IRT::Label label_;
};

std::ostream& operator<<(std::ostream&, const Label&);

}
