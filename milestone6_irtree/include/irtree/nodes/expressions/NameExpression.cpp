//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/expressions/NameExpression.hpp"

namespace IRT {

NameExpression::NameExpression(Label label): label(label) {
}

void NameExpression::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
