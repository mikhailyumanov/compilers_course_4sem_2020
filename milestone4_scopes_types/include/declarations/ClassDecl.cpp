#include "declarations/ClassDecl.hpp"


ClassDecl::ClassDecl(const std::string& class_name, 
    std::shared_ptr<DeclList> decl_list)
  : class_name{class_name}, decl_list{decl_list} {
}

void ClassDecl::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
