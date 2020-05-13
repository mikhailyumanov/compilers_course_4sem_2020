#include "statements/LocalVarDeclStmt.hpp"


LocalVarDeclStmt::LocalVarDeclStmt(std::shared_ptr<VarDecl> var_decl)
  : var_decl{var_decl} {
}

void LocalVarDeclStmt::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->Visit(shared_from_this());
}

void LocalVarDeclStmt::Perform() const {
}
