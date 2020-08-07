#include "irtree/jouette_rules/MulRule.hpp"


namespace Jouette {

bool MulRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  return IRT::IsBinopExpr(element) && 
    IRT::GetBinopExpr(element)->operator_type == IRT::BinaryOperatorType::MUL;
}

}
