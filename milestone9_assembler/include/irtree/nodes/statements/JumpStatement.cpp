//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/statements/JumpStatement.hpp"

namespace IRT {

JumpStatement::JumpStatement(Label label): label(label) {
}

void JumpStatement::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
