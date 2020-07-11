#include "visitors/SymbolTreeVisitor.hpp"


SymbolTreeVisitor::SymbolTreeVisitor(const std::string& filename) 
  : tree_(std::make_shared<ScopeLayerTree>()), 
    current_scope_(tree_->GetRoot()),
    print_visitor_(std::make_shared<PrintVisitor>(filename, true)), 
    verbose_{true} {
}

SymbolTreeVisitor::SymbolTreeVisitor() 
  : tree_(std::make_shared<ScopeLayerTree>()), 
    current_scope_(tree_->GetRoot()),
    verbose_{false} {
}

void SymbolTreeVisitor::Visit(std::shared_ptr<Program> element) {
  // current_scope_ = main() scope
  if (verbose_) {
    print_visitor_->Visit(element);
  }
  ScopeDown();

  element->class_decl_list->Accept(shared_from_this());
  ScopeDown();
  element->main_class->Accept(shared_from_this());
  ScopeUp();

  if (verbose_) {
    print_visitor_->GoUp();
  }
}


void SymbolTreeVisitor::Visit(std::shared_ptr<MainClass> element) {
  // current_scope_ = main() scope
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->stmt_list->Accept(shared_from_this());

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<AssertStmt> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->expr->Accept(shared_from_this());

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<LocalVarDeclStmt> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->var_decl->Accept(shared_from_this());

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<StmtListStmt> element) {
  ScopeDown();
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->stmt_list->Accept(shared_from_this());
  ScopeUp();

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IfStmt> element) {
//  Why not ScopeDown? If there is StmtListStmt, it will. 
//  Else, there is a single expr, for example, useless VarDecl.
//  If so, TODO: print warning

//  ScopeDown();
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->expr->Accept(shared_from_this());
  element->stmt->Accept(shared_from_this());
//  ScopeUp();

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IfElseStmt> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->expr->Accept(shared_from_this());

//  Unlike the IfStmt above, ScopeDown is necessary here!
//  Case: if-stmt false, go to else-stmt? 
//        No, iterator goes to if-stmt instead of else-stmt.
//  Solution: 1) surround 'Accepts' with scope-down/up here
//            2) scopedown + scopeup both of stmt (if, else) 
//               in interpreter even if one of them is not evaluated.

  ScopeDown();
  element->stmt_true->Accept(shared_from_this());
  ScopeUp();

  ScopeDown();
  element->stmt_false->Accept(shared_from_this());
  ScopeUp();

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<WhileStmt> element) {
//  Why not ScopeDown? See IfStmt
//  ScopeDown();
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->expr->Accept(shared_from_this());

  element->stmt->Accept(shared_from_this());
//  ScopeUp();

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<PrintStmt> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->expr->Accept(shared_from_this());

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<AssignmentStmt> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->lvalue->Accept(shared_from_this());
  element->expr->Accept(shared_from_this());

  auto object = current_scope_->Get(element->lvalue->name);
  Type expr_type = element->expr->GetType();

  if ((object->IsArray() && !element->lvalue->expr) ^
      expr_type.is_array) {
    throw std::runtime_error("Exactly one of types is non-array.");
  }

  if (object->GetType().IsIntegral() ^ expr_type.IsIntegral()) {
    throw std::runtime_error("Exactly one of types is not integral.");
  } else {
    if (!expr_type.IsIntegral() && 
        object->GetType().type != expr_type.type) {
      throw std::runtime_error("Cannot cast.");
    }
  }

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<BinOpExpr> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->lhs->Accept(shared_from_this());
  if (verbose_) 
    print_visitor_->GetStream() << (int) element->op << std::endl;
  element->rhs->Accept(shared_from_this());

  Type lt = element->lhs->GetType();
  Type rt = element->rhs->GetType();

  if (lt.is_array || rt.is_array) {
    throw std::runtime_error("Cannot perform bin operation over array.");
  }

  if (element->op <= BinOpExpr::Operation::OP_EQUAL) {
    element->SetType({"boolean", false});
  } else {
    element->SetType({"int", false});
  }

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<SubscriptExpr> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->expr->Accept(shared_from_this());
  element->idx->Accept(shared_from_this());

  Type expr_type = element->expr->GetType();
  if (!expr_type.is_array) {
    throw std::runtime_error("Cannot subscript non-array.");
  }

  Type idx_type = element->idx->GetType();
  if (idx_type.is_array) {
    throw std::runtime_error("Index should be of non-array type.");
  }

  if (!idx_type.IsIntegral()) {
    throw std::runtime_error("Index must be integral.");
  }

  // there are no n-dim arrays with n > 1
  element->SetType({expr_type.type, false}); 

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<LengthExpr> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->expr->Accept(shared_from_this());

  Type expr_type = element->expr->GetType();
  if (!expr_type.is_array) {
    throw std::runtime_error("Non-array type has not length.");
  }

  element->SetType({"int", false});

  if (verbose_) {
    print_visitor_->GoUp();
  }
}


void SymbolTreeVisitor::Visit(std::shared_ptr<TrueExpr> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->SetType({"boolean", false});
}

void SymbolTreeVisitor::Visit(std::shared_ptr<FalseExpr> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->SetType({"boolean", false});
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IntExpr> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->SetType({"int", false});
}

void SymbolTreeVisitor::Visit(std::shared_ptr<NewExpr> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->SetType({element->type, false});
}

void SymbolTreeVisitor::Visit(std::shared_ptr<NewArrayExpr> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->expr->Accept(shared_from_this());

  Type expr_type = element->expr->GetType();
  if (expr_type.is_array) {
    throw std::runtime_error("Array size must be of non-array type.");
  }

  if (!expr_type.IsIntegral()) {
    throw std::runtime_error("Array size must be integral.");
  }

  element->SetType({element->type, true});

  if (verbose_) {
    print_visitor_->GoUp();
  }
}


void SymbolTreeVisitor::Visit(std::shared_ptr<NotExpr> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->expr->Accept(shared_from_this());

  Type expr_type = element->expr->GetType();
  if (expr_type.is_array) {
    throw std::runtime_error("'Not'-expression must be of non-array type.");
  }

  element->SetType({"boolean", false});

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IdentExpr> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  // check if declared
  if (!current_scope_->IsDeclaredAnywhere(element->name)) {
    throw std::runtime_error("Variable is not declared.");
  }

  element->SetType(current_scope_->Get(element->name)->GetType());
}

void SymbolTreeVisitor::Visit(std::shared_ptr<ClassDecl> element) {
  ScopeDown();
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  element->decl_list->Accept(shared_from_this());
  ScopeUp();

  // TODO

  if (verbose_) {
    print_visitor_->GoUp();
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<VarDecl> element) {
  if (verbose_) {
    print_visitor_->Visit(element);
  }

  DEBUG_START DEBUG(element->name) DEBUG(element->type) DEBUG_FINISH
  current_scope_->DeclareVariable(element->name, element->type);
}

void SymbolTreeVisitor::Visit(std::shared_ptr<Lvalue> element) {
  if (verbose_) {
    print_visitor_->Visit(element);

  }

  // check if declared
  if (!current_scope_->IsDeclaredAnywhere(element->name)) {
    throw std::runtime_error("Variable is not declared.");
  }

  if (element->expr) {
    auto object = current_scope_->Get(element->name);

    // check if object is array
    if (!object->IsArray()) {
      throw std::runtime_error("Subscription of non-array is restricted.");
    }

    element->expr->Accept(shared_from_this());

    Type expr_type = element->expr->GetType();

    if (expr_type.is_array) {
      throw std::runtime_error("Index should be of non-array type.");
    }
   
    if (!expr_type.IsIntegral()) {
      throw std::runtime_error("Index must be integral.");
    }


    if (verbose_) {
      print_visitor_->GoUp();
    }
  }
}


std::shared_ptr<ScopeLayerTree> SymbolTreeVisitor::GetTree() const {
  return tree_;
}


void SymbolTreeVisitor::ScopeDown() {
  if (verbose_) {
    print_visitor_->PrintTabs();
    print_visitor_->GetStream() << "NEW SCOPE" << std::endl;
  }

//  current_scope_ = tree_->AddLayer(current_scope_);
  tree_->AddLayer(*current_scope_);
  current_scope_.GoDown();
}

void SymbolTreeVisitor::ScopeUp() {
//  current_scope_ = current_scope_->GetParent();
  current_scope_.GoUp();
}

