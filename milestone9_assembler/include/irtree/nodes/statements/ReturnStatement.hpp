#pragma once

#include "irtree/nodes/statements/Statement.hpp"
#include "irtree/generators/Label.hpp"


namespace IRT {

class ReturnStatement: public Statement,
  public std::enable_shared_from_this<ReturnStatement> {
 public:
  void Accept(std::shared_ptr<Visitor> visitor) override;
};

}

