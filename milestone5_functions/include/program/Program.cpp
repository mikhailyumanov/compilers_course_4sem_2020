#include "program/Program.hpp"


Program::Program(std::shared_ptr<MainClass> main_class,
    std::shared_ptr<ClassDeclList> class_decl_list)
  : main_class{main_class}, class_decl_list{class_decl_list} {
}

Program::Program(std::shared_ptr<MainClass> main_class)
  : Program(main_class, std::make_shared<ClassDeclList>()) {
}

void Program::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
