#pragma once

#include "declarations/Decl.hpp"
#include "statements/StmtList.hpp"
#include "types/FunctionType.hpp"


class MethodDecl: virtual public Decl,
  public std::enable_shared_from_this<MethodDecl> {
 public:
  MethodDecl(FunctionType function_type, const std::string& name, 
      std::shared_ptr<StmtList> stmt_list);
  void Accept(std::shared_ptr<Visitor> visitor) override;

  FunctionType function_type;
  std::string name;
  std::shared_ptr<StmtList> stmt_list;
};
