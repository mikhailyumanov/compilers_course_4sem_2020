#include "irtree/jouette_rules/AddRule.hpp"


namespace Jouette {

bool AddRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsBinopExpr(element) && 
    IRT::GetBinopExpr(element)->operator_type == IRT::BinaryOperatorType::PLUS;
}

}
