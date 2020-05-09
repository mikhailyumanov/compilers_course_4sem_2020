#pragma once

#include <memory>

#include "program/MainClass.hpp"
#include "program/ClassDeclList.hpp"


class Program : enable_shared_from_this<Program> {
 public:
  Program(std::shared_ptr<MainClass> main_class,
      std::shared_ptr<ClassDeclList> class_decl_list);

  Program(std::shared_ptr<MainClass> main_class);

 private:
  std::shared_ptr<MainClass> main_class_;
  std::shared_ptr<ClassDeclList> class_decl_list_;
};
