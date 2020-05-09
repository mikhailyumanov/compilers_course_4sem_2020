#pragma once

#include <memory>

#include "statements/StmtList.hpp"


class MainClass : std::enable_shared_from_this<MainClass> {
 public:
  MainClass(std::shared_ptr<StmtList> stmt_list);

 private:
  std::shared_ptr<StmtList> stmt_list_;
};
