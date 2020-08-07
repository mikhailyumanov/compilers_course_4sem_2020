#include "irtree/jouette_rules/SubiRule.hpp"


namespace Jouette {

bool SubiRule::IsSuitable(std::shared_ptr<IRT::BaseElement> element) const {
  std::shared_ptr<IRT::BinopExpression> expr;
  return IRT::IsBinopExpr(element) && 
    (expr = IRT::GetBinopExpr(element), 
     expr->operator_type == IRT::BinaryOperatorType::MINUS) &&
    IRT::IsConstExpr(expr->rhs);
}

}
