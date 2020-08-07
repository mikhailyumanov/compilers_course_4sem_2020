#include "jouette/instructions/commands/LoadStore.hpp"

namespace Jouette {

Load::Load(std::shared_ptr<Register> output, std::shared_ptr<Register> input, 
    int cnst)
  : output{output}, input{input}, cnst{cnst} {
}

void Load::Accept(std::shared_ptr<Jouette::Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

Store::Store(std::shared_ptr<Register> output, int cnst, 
    std::shared_ptr<Register> input)
  : output{output}, cnst{cnst}, input{input} {
}

void Store::Accept(std::shared_ptr<Jouette::Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

}
