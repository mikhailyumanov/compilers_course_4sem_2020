#include "irtree/jouette_rules/StoreConstRule.hpp"
#include "irtree/jouette_rules/LoadConstRule.hpp"


namespace Jouette {

bool StoreConstRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsMoveStmt(element) &&
    LoadConstRule().IsSuitable(IRT::GetMoveStmt(element)->target);
}

}
