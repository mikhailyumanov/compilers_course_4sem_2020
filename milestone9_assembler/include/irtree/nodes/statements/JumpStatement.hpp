//
// Created by akhtyamovpavel on 4/14/20.
// Modified by Mikhail Yumanov on 7/21/20
//

#pragma once

#include "irtree/nodes/statements/Statement.hpp"
#include "irtree/generators/Label.hpp"


namespace IRT {

class JumpStatement: public Statement,
  public std::enable_shared_from_this<JumpStatement> {
 public:
  explicit JumpStatement(Label label);

  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  Label label;
};

}

