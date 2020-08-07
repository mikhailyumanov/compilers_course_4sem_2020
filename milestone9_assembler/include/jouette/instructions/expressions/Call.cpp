#include "jouette/instructions/expressions/Call.hpp"


namespace Jouette {

Call::Call(std::shared_ptr<Register> output, Label label, 
    std::vector<std::shared_ptr<Register>> args)
  : Expression{output}, label{label}, args{std::move(args)} {
}

void Call::Accept(std::shared_ptr<Jouette::Visitor> visitor) {
  visitor->Visit(this->shared_from_this());
}

}
