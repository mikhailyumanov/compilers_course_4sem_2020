#include "declarations/ClassDecl.hpp"


ClassDecl::ClassDecl(std::shared_ptr<DeclList> decl_list)
  : decl_list{decl_list} {
}

void ClassDecl::Accept(std::shared_ptr<Visitor> visitor) {
}
