#include "irtree/jouette_rules/SubRule.hpp"


namespace Jouette {

bool SubRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsBinopExpr(element) && 
    IRT::GetBinopExpr(element)->operator_type == IRT::BinaryOperatorType::MINUS;
}

}
