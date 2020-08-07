#include "irtree/jouette_rules/StoreRule.hpp"
#include "irtree/jouette_rules/LoadRule.hpp"


namespace Jouette {

bool StoreRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsMoveStmt(element) &&
    LoadRule().IsSuitable(IRT::GetMoveStmt(element)->target);
}

}
