#include "irtree/jouette_rules/AddiConstRule.hpp"


namespace Jouette {

bool AddiConstRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsConstExpr(element);
}

}
