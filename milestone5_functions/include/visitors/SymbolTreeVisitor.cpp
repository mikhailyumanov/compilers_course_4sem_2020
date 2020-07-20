#include "visitors/SymbolTreeVisitor.hpp"

#define PRINT_DOWN if (verbose_) { print_visitor_->Visit(element); }

// Use PRINT_UP where GO_DOWN/UP is used in PrintVisitor
#define PRINT_UP if (verbose_) { print_visitor_->GoUp(); }

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
  PRINT_DOWN
  ScopeDown();

  current_scope_->UnsetMain();
  element->class_decl_list->Accept(shared_from_this());

  ScopeDown();
  current_scope_->SetMain();
  element->main_class->Accept(shared_from_this());
  ScopeUp();

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<MainClass> element) {
  // current_scope_ = main() scope
  PRINT_DOWN

  current_scope_->SetMain();
  element->stmt_list->Accept(shared_from_this());

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<AssertStmt> element) {
  PRINT_DOWN

  element->expr->Accept(shared_from_this());

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<LocalVarDeclStmt> element) {
  PRINT_DOWN

  element->var_decl->Accept(shared_from_this());

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<StmtListStmt> element) {
  ScopeDown();
  PRINT_DOWN

  element->stmt_list->Accept(shared_from_this());
  ScopeUp();

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IfStmt> element) {
//  Why not ScopeDown? If there is StmtListStmt, it will. 
//  Else, there is a single expr, for example, useless VarDecl.
//  If so, TODO: print warning
//
//  Later:
//  ScopeDown is EXTREMELY NECESSARY! See test7

  ScopeDown();
  PRINT_DOWN

  element->expr->Accept(shared_from_this());
  element->stmt->Accept(shared_from_this());
  ScopeUp();

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IfElseStmt> element) {
  PRINT_DOWN

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

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<WhileStmt> element) {
//  ScopeDown or not??? IDK!!!
//  But if change, deal with it in Interpreter too
//
//  Later: after XX hours debugging IfStmt, I DO surround it with ScopeDown
//  to avoid any problems in future.
//  Dear future me or anyone using it: please, DO NOT SAVE ON SCOPEDOWNS

  ScopeDown();
  PRINT_DOWN

  element->expr->Accept(shared_from_this());

  element->stmt->Accept(shared_from_this());
  ScopeUp();

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<PrintStmt> element) {
  PRINT_DOWN

  element->expr->Accept(shared_from_this());

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<AssignmentStmt> element) {
  PRINT_DOWN

  element->lvalue->Accept(shared_from_this());
  element->expr->Accept(shared_from_this());

  Type expr_type = element->expr->GetType();
  Type object_type = current_scope_->GetType(element->lvalue->name);

  if ((object_type.is_array && !element->lvalue->expr) ^
      expr_type.is_array) {
    throw std::runtime_error("Exactly one of types is non-array: " +
        object_type.ToString() + " and " + expr_type.ToString());
  }

  if (object_type.IsIntegral() ^ expr_type.IsIntegral()) {
    throw std::runtime_error("Exactly one of types is not integral: " +
        object_type.ToString() + " and " + expr_type.ToString());
  } else {
    if (!expr_type.IsIntegral() && 
        object_type.type != expr_type.type) {
      throw std::runtime_error("Cannot cast: " +
        object_type.ToString() + " and " + expr_type.ToString());
    }
  }

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<ReturnStmt> element) {
  PRINT_DOWN

  element->expr->Accept(shared_from_this());

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<MethodStmt> element) {
  PRINT_DOWN

  element->invocation->Accept(shared_from_this());

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<BinOpExpr> element) {
  PRINT_DOWN

  element->lhs->Accept(shared_from_this());
  if (verbose_) 
    print_visitor_->GetStream() << (int) element->op << std::endl;
  element->rhs->Accept(shared_from_this());

  Type lt = element->lhs->GetType();
  Type rt = element->rhs->GetType();

  if (lt.is_array || rt.is_array) {
    throw std::runtime_error("Cannot perform bin operation over array: " +
        lt.ToString() + " and " + rt.ToString());
  }

  if (element->op <= BinOpExpr::Operation::OP_EQUAL) {
    element->SetType({"boolean", false});
  } else {
    element->SetType({"int", false});
  }

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<SubscriptExpr> element) {
  PRINT_DOWN

  element->expr->Accept(shared_from_this());
  element->idx->Accept(shared_from_this());

  Type expr_type = element->expr->GetType();
  if (!expr_type.is_array) {
    throw std::runtime_error(
        "Cannot subscript non-array: " + expr_type.ToString());
  }

  Type idx_type = element->idx->GetType();
  if (idx_type.is_array) {
    throw std::runtime_error(
        "Index should be of non-array type: " + idx_type.ToString());
  }

  if (!idx_type.IsIntegral()) {
    throw std::runtime_error("Index must be integral: " + idx_type.ToString());
  }

  // there are no n-dim arrays with n > 1
  element->SetType({expr_type.type, false}); 

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<LengthExpr> element) {
  PRINT_DOWN

  element->expr->Accept(shared_from_this());

  Type expr_type = element->expr->GetType();
  if (!expr_type.is_array) {
    throw std::runtime_error(
        "Non-array type has not length: " + expr_type.ToString());
  }

  element->SetType({"int", false});

  PRINT_UP
}


void SymbolTreeVisitor::Visit(std::shared_ptr<TrueExpr> element) {
  PRINT_DOWN

  element->SetType({"boolean", false});
}

void SymbolTreeVisitor::Visit(std::shared_ptr<FalseExpr> element) {
  PRINT_DOWN

  element->SetType({"boolean", false});
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IntExpr> element) {
  PRINT_DOWN

  element->SetType({"int", false});
}

void SymbolTreeVisitor::Visit(std::shared_ptr<NewExpr> element) {
  PRINT_DOWN

  element->SetType({element->type, false});
}

void SymbolTreeVisitor::Visit(std::shared_ptr<NewArrayExpr> element) {
  PRINT_DOWN

  element->expr->Accept(shared_from_this());

  Type expr_type = element->expr->GetType();
  if (expr_type.is_array) {
    throw std::runtime_error(
        "Array size must be of non-array type: " + expr_type.ToString());
  }

  if (!expr_type.IsIntegral()) {
    throw std::runtime_error(
        "Array size must be integral: " + expr_type.ToString());
  }

  element->SetType({element->type, true});

  PRINT_UP
}


void SymbolTreeVisitor::Visit(std::shared_ptr<NotExpr> element) {
  PRINT_DOWN

  element->expr->Accept(shared_from_this());

  Type expr_type = element->expr->GetType();
  if (expr_type.is_array) {
    throw std::runtime_error(
        "'Not'-expression must be of non-array type: " + expr_type.ToString());
  }

  element->SetType({"boolean", false});

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<IdentExpr> element) {
  PRINT_DOWN

  // check if declared
  if (!current_scope_->IsDeclaredAnywhere(element->name)) {
    throw std::runtime_error("Variable is not declared: " + element->name);
  }

  element->SetType(current_scope_->GetType(element->name));
}

void SymbolTreeVisitor::Visit(std::shared_ptr<MethodExpr> element) {
  PRINT_DOWN

  element->invocation->Accept(shared_from_this());

  Type method_type = FunctionStorage::GetInstance().GetFunction(
        element->invocation->expr->GetType().type, 
        element->invocation->func_name)->function_type.GetReturnType();
  element->SetType(method_type);

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<ThisExpr> element) {
  PRINT_DOWN

  if (current_scope_->IsMain()) {
    throw std::runtime_error("Cannot use 'this' keyword im main() context.");
  }

  element->SetType(Type{current_class_, false});
}

void SymbolTreeVisitor::Visit(std::shared_ptr<ClassDecl> element) {
  ScopeDown();
  PRINT_DOWN

  current_class_ = element->class_name;
  FunctionStorage::GetInstance().DeclareClass(current_class_);

  element->decl_list->Accept(shared_from_this());
  ScopeUp();

  PRINT_UP
}

void SymbolTreeVisitor::Visit(std::shared_ptr<VarDecl> element) {
  PRINT_DOWN

  DEBUG_START DEBUG(element->name) DEBUG(element->type) DEBUG_FINISH
  current_scope_->DeclareVariable(element->name, element->type);

  if (!current_scope_->IsMain() && !IsMethodDeclaration()) {
    DEBUG_SINGLE("VarDecl: IsMethodDecl")
    std::make_shared<ClassBuilder>()->SetClassParam(
        current_class_, element->name, element->type);
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<MethodDecl> element) {
  FunctionScopeDown(element->function_type);
  PRINT_DOWN

  DEBUG_START
    DEBUG(element->name)
    DEBUG(element->function_type)
    DEBUG(current_scope_->GetFunctionType())
  DEBUG_FINISH

//  ScopeDown();
  SetMethodDecl();

  FunctionStorage::GetInstance().DeclareFunction(
      current_class_, element->name, element->function_type);
  element->stmt_list->Accept(shared_from_this());

  UnsetMethodDecl();
//  ScopeUp();

  DEBUG_START
    DEBUG("MethodDecl: ")
    DEBUG(element->function_type)
    DEBUG(current_scope_->GetFunctionType())
  DEBUG_FINISH

  FunctionStorage::GetInstance().SetFunction(current_class_, element->name,
      std::make_shared<Function>(element->function_type, element->stmt_list));

  DEBUG_SINGLE(current_scope_->GetFunctionType())
  tree_->SetFunctionScope(current_class_, element->name, *current_scope_);

  PRINT_UP
  ScopeUp();
}

void SymbolTreeVisitor::Visit(std::shared_ptr<Lvalue> element) {
  PRINT_DOWN

  // check if declared
  if (!current_scope_->IsDeclaredAnywhere(element->name)) {
    throw std::runtime_error("Variable is not declared: " + element->name);
  }

  if (element->expr) {
    Type object_type = current_scope_->GetType(element->name);

    // check if object is array
    if (!object_type.is_array) {
      throw std::runtime_error("Subscription of non-array is restricted: " +
          object_type.ToString());
    }

    element->expr->Accept(shared_from_this());

    Type expr_type = element->expr->GetType();

    if (expr_type.is_array) {
      throw std::runtime_error(
          "Index should be of non-array type: " + expr_type.ToString());
    }
   
    if (!expr_type.IsIntegral()) {
      throw std::runtime_error(
          "Index must be integral: " + expr_type.ToString());
    }


    PRINT_UP
  }
}

void SymbolTreeVisitor::Visit(std::shared_ptr<MethodInvocation> element) {
  PRINT_DOWN

  auto comma_expr_list = element->comma_expr_list;
  auto expr = element->expr;

  expr->Accept(shared_from_this());
  DEBUG_SINGLE(element->func_name)
  comma_expr_list->Accept(shared_from_this());
  std::string class_name = expr->GetType().type;
  std::string func_name = element->func_name;

  // check expr type
  if (!expr->GetType().IsClass()) {
    throw std::runtime_error("Cannot call method of non-class: " +
        expr->GetType().ToString());
  }

  // check if class exists
  if (!FunctionStorage::GetInstance().HasClass(class_name)) {
    throw std::runtime_error(
        "Class " + class_name + " is not already declared.");
  }

  // check if method exists
  if (!FunctionStorage::GetInstance().HasFunction(class_name, func_name)) {
    throw std::runtime_error(
        "Function " + class_name + "::" + func_name +
        " is not already declared.");
  }

  auto function = FunctionStorage::GetInstance().GetFunction(
      class_name, func_name);
  auto& func_type = function->function_type;
  size_t num_args = func_type.GetNumArgs();

  // check num args
  if (comma_expr_list->GetLength() != num_args) {
    throw std::runtime_error("Wrong number of arguments passed to function " +
        class_name + "::" + func_name);
  }

  // check args types
  for (size_t i = 0; i < num_args; ++i) {
    auto arg_type =
      std::dynamic_pointer_cast<Expression>((*comma_expr_list)[i])->GetType();
    if (arg_type != func_type.arg_types[i]) {
      throw std::runtime_error("Wrong type of expr in function call: got " +
          arg_type.ToString() + ", expected " +
          func_type.arg_types[i].ToString() + ".");
    }
  }

  // dummy scope for attaching function scope in Interpreter
  ScopeDown();
  ScopeUp();

  PRINT_UP
}


std::shared_ptr<ScopeLayerTree> SymbolTreeVisitor::GetTree() const {
  return tree_;
}


void SymbolTreeVisitor::ScopeDown() {
  if (verbose_) {
    print_visitor_->PrintTabs();
    print_visitor_->GetStream() << "NEW SCOPE" << std::endl;
  }

  tree_->AddLayer(*current_scope_);
  current_scope_.GoDown();
}

void SymbolTreeVisitor::ScopeUp() {
  current_scope_.GoUp();
}

void SymbolTreeVisitor::FunctionScopeDown(FunctionType function_type) {
  if (verbose_) {
    print_visitor_->PrintTabs();
    print_visitor_->GetStream() << "NEW FUNCTION SCOPE" << std::endl;
  }

  DEBUG_SINGLE("SymbolTreeVisitor::FunctionScopeDown")
  DEBUG_SINGLE(function_type)
  tree_->AddLayer(*current_scope_, function_type);
  current_scope_.GoDown();
  DEBUG_SINGLE(function_type)
}

bool SymbolTreeVisitor::SetMethodDecl() {
  method_decl_ = true;
}

bool SymbolTreeVisitor::UnsetMethodDecl() {
  method_decl_ = false;
}

bool SymbolTreeVisitor::IsMethodDeclaration() const {
  return method_decl_;
}

