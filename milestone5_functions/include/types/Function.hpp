#pragma once

#include "types/Object.hpp"
#include "types/FunctionType.hpp"
#include "statements/StmtList.hpp"


class Function : public Object {
 public:
  Function(FunctionType function_type, std::shared_ptr<StmtList> stmt_list);
  Function(FunctionType function_type);

  void Print(std::ostream& stream) const override;

  FunctionType function_type;
  std::shared_ptr<StmtList> stmt_list;
};



