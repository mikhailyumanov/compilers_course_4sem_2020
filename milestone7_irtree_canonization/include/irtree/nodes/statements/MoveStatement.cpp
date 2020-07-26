//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/nodes/statements/MoveStatement.hpp"


namespace IRT {

MoveStatement::MoveStatement(std::shared_ptr<Expression> source, 
    std::shared_ptr<Expression> target)
  : source(source), target(target) {
}

void MoveStatement::Accept(std::shared_ptr<IRT::Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
