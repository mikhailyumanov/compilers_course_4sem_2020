#include "jouette/instructions/commands/Jump.hpp"

namespace Jouette {

Jump::Jump(Label label) : label{label} {
}

void Jump::Accept(std::shared_ptr<Jouette::Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

}
