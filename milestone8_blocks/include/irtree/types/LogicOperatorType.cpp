//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#include "irtree/types/LogicOperatorType.hpp"


std::string IRT::ToString(IRT::LogicOperatorType type) {
  switch (type) {
    case LogicOperatorType::EQ: return "EQ";
    case LogicOperatorType::NE: return "NE";
    case LogicOperatorType::LT: return "LT";
    case LogicOperatorType::GT: return "GT";
  }
}
