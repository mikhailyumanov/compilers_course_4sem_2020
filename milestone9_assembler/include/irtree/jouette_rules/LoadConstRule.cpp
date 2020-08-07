#include "irtree/jouette_rules/LoadConstRule.hpp"


namespace Jouette {

bool LoadConstRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsMemExpr(element) &&
    IRT::IsConstExpr(IRT::GetMemExpr(element)->expr);
}

}
