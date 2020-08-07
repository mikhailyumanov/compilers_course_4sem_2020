#include "irtree/jouette_rules/AddiRightConstRule.hpp"


namespace Jouette {

bool AddiRightConstRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  std::shared_ptr<IRT::BinopExpression> expr;
  return IRT::IsBinopExpr(element) && 
    (expr = IRT::GetBinopExpr(element), 
     expr->operator_type == IRT::BinaryOperatorType::PLUS) &&
    IRT::IsConstExpr(expr->rhs);
}

}
