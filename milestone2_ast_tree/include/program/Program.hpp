#pragma once

#include <memory>

#include "program/MainClass.hpp"
#include "program/ClassDeclList.hpp"
#include "visitors/Visitor.hpp"


class Program: public std::enable_shared_from_this<Program> {
 public:
  Program(std::shared_ptr<MainClass> main_class,
      std::shared_ptr<ClassDeclList> class_decl_list);

  Program(std::shared_ptr<MainClass> main_class);

  void Accept(std::shared_ptr<Visitor> visitor);

  std::shared_ptr<MainClass> main_class;
  std::shared_ptr<ClassDeclList> class_decl_list;
};
