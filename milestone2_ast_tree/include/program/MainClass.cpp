#include "program/MainClass.hpp"


MainClass::MainClass(std::shared_ptr<StmtList> stmt_list)
  : stmt_list{stmt_list} {
}

void MainClass::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}
