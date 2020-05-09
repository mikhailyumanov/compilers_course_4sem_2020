#include "program/Program.hpp"


Program::Program(std::shared_ptr<MainClass> main_class,
    std::shared_ptr<ClassDeclList> class_decl_list)
  : main_class_{main_class}, class_decl_list_{class_decl_list} {
}

Program::Program(std::shared_ptr<MainClass> main_class)
  : Program(main_class, std::shared_ptr<ClassDeclList>()) {
}
