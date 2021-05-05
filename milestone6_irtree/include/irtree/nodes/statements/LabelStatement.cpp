//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/statements/LabelStatement.hpp"

namespace IRT {

LabelStatement::LabelStatement(IRT::Label label): label(label) {
} 

void LabelStatement::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
