#include "declarations/MethodDecl.hpp"

MethodDecl::MethodDecl(FunctionType function_type, const std::string& name,
    std::shared_ptr<StmtList> stmt_list)
  : function_type{function_type}, name{name}, stmt_list{stmt_list} {
}

void MethodDecl::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
