#pragma once

#include "functions/address/Address.hpp"
#include "irtree/nodes/expressions/Expression.hpp"


namespace IRT {

class AddressInFrame: public Address,
  public std::enable_shared_from_this<AddressInFrame> {
 public:
  AddressInFrame(std::shared_ptr<Address> frame_address,
      std::shared_ptr<IRT::Expression> offset);
  ~AddressInFrame() = default;

  std::shared_ptr<IRT::Expression> ToExpression() override;
  void AddOffset(std::shared_ptr<IRT::Expression>);

 private:
  std::shared_ptr<Address> frame_address_;
  std::shared_ptr<IRT::Expression> offset_;
};

}
