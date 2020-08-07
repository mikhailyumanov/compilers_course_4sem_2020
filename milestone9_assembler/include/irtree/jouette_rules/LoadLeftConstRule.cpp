#include "irtree/jouette_rules/LoadLeftConstRule.hpp"
#include "irtree/jouette_rules/AddiLeftConstRule.hpp"


namespace Jouette {

bool LoadLeftConstRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsMemExpr(element) &&
    AddiLeftConstRule().IsSuitable(IRT::GetMemExpr(element)->expr);
}

}
