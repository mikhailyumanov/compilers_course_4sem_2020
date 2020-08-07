#include "irtree/jouette_rules/StoreRightConstRule.hpp"
#include "irtree/jouette_rules/LoadRightConstRule.hpp"


namespace Jouette {

bool StoreRightConstRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsMoveStmt(element) &&
    LoadRightConstRule().IsSuitable(IRT::GetMoveStmt(element)->target);
}

}
