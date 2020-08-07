#include "irtree/jouette_rules/StoreLeftConstRule.hpp"
#include "irtree/jouette_rules/LoadLeftConstRule.hpp"


namespace Jouette {

bool StoreLeftConstRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsMoveStmt(element) &&
    LoadLeftConstRule().IsSuitable(IRT::GetMoveStmt(element)->target);
}

}
