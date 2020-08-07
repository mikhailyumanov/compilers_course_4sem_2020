#include "jouette/instructions/commands/Return.hpp"

namespace Jouette {

Return::Return() {
}

void Return::Accept(std::shared_ptr<Jouette::Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

}
