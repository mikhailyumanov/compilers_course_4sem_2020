#include "jouette/instructions/commands/Label.hpp"

namespace Jouette {

Label::Label(IRT::Label label) : label_{label} {
}

void Label::Accept(std::shared_ptr<Jouette::Visitor> visitor) {
  DEBUG_SINGLE("Label::Accept")
  visitor->Visit(this->shared_from_this());
}

Label::operator std::string() const {
  return label_.ToString();
}

std::ostream& operator<<(std::ostream& os, const Label& label) {
  DEBUG_SINGLE("Label operator<<")
  os << (std::string) label;
  DEBUG_SINGLE("Label operator<< (end)")
  return os;
}

}
