#include "functions/address/AddressInFrame.hpp"
#include "irtree/nodes/expressions/BinopExpression.hpp"
#include "irtree/nodes/expressions/ConstExpression.hpp"
#include "irtree/nodes/expressions/MemExpression.hpp"


namespace IRT {

AddressInFrame::AddressInFrame(
    std::shared_ptr<Address> frame_address,
    std::shared_ptr<IRT::Expression> offset)
  : frame_address_(frame_address), offset_(offset) {
}

std::shared_ptr<Expression> AddressInFrame::ToExpression() {
  std::shared_ptr<Expression> offset_expression = 
    std::make_shared<BinopExpression>(
      BinaryOperatorType::PLUS,
      frame_address_->ToExpression(),
      offset_
  );

  return std::make_shared<MemExpression>(offset_expression);
}

void AddressInFrame::AddOffset(std::shared_ptr<IRT::Expression> expr) {
  offset_ = std::make_shared<IRT::BinopExpression>(
      IRT::BinaryOperatorType::PLUS,
      expr,
      offset_
  );
}

}
