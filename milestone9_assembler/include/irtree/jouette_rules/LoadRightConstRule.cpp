#include "irtree/jouette_rules/LoadRightConstRule.hpp"
#include "irtree/jouette_rules/AddiRightConstRule.hpp"


namespace Jouette {

bool LoadRightConstRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsMemExpr(element) &&
    AddiRightConstRule().IsSuitable(IRT::GetMemExpr(element)->expr);
}

}
