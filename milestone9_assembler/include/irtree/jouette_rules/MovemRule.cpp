#include "irtree/jouette_rules/MovemRule.hpp"
#include "irtree/jouette_rules/LoadRule.hpp"


namespace Jouette {

bool MovemRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  std::shared_ptr<IRT::MoveStatement> stmt;
  return IRT::IsMoveStmt(element) && (stmt = IRT::GetMoveStmt(element), 
    LoadRule().IsSuitable(stmt->target)) &&
    LoadRule().IsSuitable(stmt->source);
}

}
