#include "irtree/nodes/statements/ReturnStatement.hpp"


namespace IRT {

void ReturnStatement::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
