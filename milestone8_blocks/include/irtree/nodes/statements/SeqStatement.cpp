//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yuanov on 7/21/20
//

#include "irtree/nodes/statements/SeqStatement.hpp"


namespace IRT {

SeqStatement::SeqStatement(std::shared_ptr<Statement> first,
    std::shared_ptr<Statement> second)
  : lhs(first), rhs(second) {
}

void SeqStatement::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

}
