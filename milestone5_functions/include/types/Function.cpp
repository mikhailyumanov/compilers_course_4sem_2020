#include "types/Function.hpp"


Function::Function(FunctionType function_type, std::shared_ptr<StmtList> stmt_list)
  : function_type{function_type}, stmt_list{stmt_list} {
}

void Function::Print(std::ostream& stream) const {
  stream << function_type << std::endl;
}
