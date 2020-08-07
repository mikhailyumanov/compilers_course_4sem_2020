#include "irtree/jouette_rules/LoadRule.hpp"


namespace Jouette {

bool LoadRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsMemExpr(element);
}

}
