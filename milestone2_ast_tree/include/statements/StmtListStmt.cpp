#include "statements/StmtListStmt.hpp"


StmtListStmt::StmtListStmt(std::shared_ptr<StmtList> stmt_list)
  : stmt_list{stmt_list} {
}

void StmtListStmt::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

void StmtListStmt::Perform() const {
  for (auto item : stmt_list->items) {
    std::dynamic_pointer_cast<Statement>(item)->Perform();
  }
}
