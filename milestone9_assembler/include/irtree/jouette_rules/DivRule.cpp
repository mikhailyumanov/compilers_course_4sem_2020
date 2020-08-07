#include "irtree/jouette_rules/DivRule.hpp"


namespace Jouette {

bool DivRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsBinopExpr(element) && 
    IRT::GetBinopExpr(element)->operator_type == IRT::BinaryOperatorType::DIV;
}

}
