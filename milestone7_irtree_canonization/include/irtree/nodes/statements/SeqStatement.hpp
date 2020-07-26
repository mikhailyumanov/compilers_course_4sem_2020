//
// Created by akhtyamovpavel on 4/8/20.
// Modified by Mikhail Yuanov on 7/21/20
//

#pragma once

#include "irtree/nodes/statements/Statement.hpp"


namespace IRT {
class SeqStatement: public Statement,
  public std::enable_shared_from_this<SeqStatement> {
 public:
  SeqStatement(std::shared_ptr<Statement> first,
     std::shared_ptr<Statement> second);

  void Accept(std::shared_ptr<Visitor> visitor) override;

 public:
  std::shared_ptr<Statement> lhs;
  std::shared_ptr<Statement> rhs;
};

}


