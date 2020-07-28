#pragma once

#include "declarations/Decl.hpp"
#include "declarations/DeclList.hpp"
#include "visitors/Visitor.hpp"


class ClassDecl: public Decl,
  public std::enable_shared_from_this<ClassDecl> {
 public:
  ClassDecl(const std::string& class_name, std::shared_ptr<DeclList> decl_list);
  void Accept(std::shared_ptr<Visitor> visitor) override;

  std::string class_name;
  std::shared_ptr<DeclList> decl_list;
};
