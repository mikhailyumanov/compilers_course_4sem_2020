#pragma once

#include <memory>

#include "visitors/Visitor.hpp"


class MainClass: public std::enable_shared_from_this<MainClass> {
 public:
  MainClass(std::shared_ptr<StmtList> stmt_list);

  void Accept(std::shared_ptr<Visitor> visitor);

  std::shared_ptr<StmtList> stmt_list;
};
