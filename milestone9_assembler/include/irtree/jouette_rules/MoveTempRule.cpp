#include "irtree/jouette_rules/MoveTempRule.hpp"


namespace Jouette {

bool MoveTempRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsMoveStmt(element) &&
    IRT::IsTempExpr(GetMoveStmt(element)->target);
}

}
