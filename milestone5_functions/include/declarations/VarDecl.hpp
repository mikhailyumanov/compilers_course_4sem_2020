#pragma once

#include "declarations/Decl.hpp"


class VarDecl: virtual public Decl,
  public std::enable_shared_from_this<VarDecl> {
 public:
  VarDecl(Type type, const std::string& name);
  void Accept(std::shared_ptr<Visitor> visitor) override;

  Type type;
  std::string name;
};
