#include "visitors/Interpreter.hpp"

struct AssertException {};

Interpreter::Interpreter(const std::string& filename)
  : tos_value_{std::make_shared<Integer>(0)},
    symbol_tree_visitor_(std::make_shared<SymbolTreeVisitor>(filename)) {
}

Interpreter::Interpreter()
  : tos_value_{std::make_shared<Integer>(0)},
    symbol_tree_visitor_(std::make_shared<SymbolTreeVisitor>()) {
}

void Interpreter::Visit(std::shared_ptr<Program> element) {
  DEBUG_SINGLE(">>> Interpreter: Program")

  // Build symbol tree
  symbol_tree_visitor_->Visit(element);
  DEBUG_START DEBUG_FINISH DEBUG_START DEBUG_FINISH
  // Init tree iterator
  
  current_scope_ = ScopeLayerTree::Iterator(
      symbol_tree_visitor_->GetTree()->GetRoot());

  current_scope_.GoDown();

  element->class_decl_list->Accept(shared_from_this());

  current_scope_.GoDown();
  element->main_class->Accept(shared_from_this());
  current_scope_.GoUp();
}

void Interpreter::Visit(std::shared_ptr<MainClass> element) {
  DEBUG_SINGLE(">>> Interpreter: MainClass")

  element->stmt_list->Accept(shared_from_this());
}

void Interpreter::Visit(std::shared_ptr<AssertStmt> element) {
  DEBUG_SINGLE(">>> Interpreter: AssertStmt")

  if (!Accept(element->expr)->ToBool()) {
    throw AssertException();
  }
}

void Interpreter::Visit(std::shared_ptr<LocalVarDeclStmt> element) {
  DEBUG_SINGLE(">>> Interpreter: LocalVarDeclStmt")

  element->var_decl->Accept(shared_from_this());
}

void Interpreter::Visit(std::shared_ptr<StmtListStmt> element) {
  DEBUG_SINGLE(">>> Interpreter: StmtListStmt")

  current_scope_.GoDown();
  element->stmt_list->Accept(shared_from_this());
  current_scope_.GoUp();
}

void Interpreter::Visit(std::shared_ptr<IfStmt> element) {
  DEBUG_SINGLE(">>> Interpreter: IfStmt")

  current_scope_.GoDown();
  if (Accept(element->expr)->ToBool()) { 
    element->stmt->Accept(shared_from_this()); 
  }
  current_scope_.GoUp();
}

void Interpreter::Visit(std::shared_ptr<IfElseStmt> element) {
  DEBUG_SINGLE(">>> Interpreter: IfElseStmt")

  if (Accept(element->expr)->ToBool()) { 
    current_scope_.GoDown();
    tos_value_ = Accept(element->stmt_true);
    current_scope_.GoUp();
    current_scope_.GoDown();
    current_scope_.GoUp();
  } else {
    current_scope_.GoDown();
    current_scope_.GoUp();
    current_scope_.GoDown();
    tos_value_ = Accept(element->stmt_false);
    current_scope_.GoUp();
  }
}

void Interpreter::Visit(std::shared_ptr<WhileStmt> element) {
  DEBUG_SINGLE(">>> Interpreter: WhileStmt")

  auto old_current_scope = current_scope_;
  auto new_current_scope = current_scope_;
  bool true_stmt = false;

  while (Accept(element->expr)->ToBool()) {
    true_stmt = true;

    current_scope_.GoDown();
    element->stmt->Accept(shared_from_this()); 
    current_scope_.GoUp();

    new_current_scope = current_scope_;
    current_scope_ = old_current_scope;
  }
  current_scope_ = new_current_scope;

  if (!true_stmt) {
    current_scope_.GoDown();
    current_scope_.GoUp();
  }
}

void Interpreter::Visit(std::shared_ptr<PrintStmt> element) {
  DEBUG_SINGLE(">>> Interpreter: PrintStmt")

  Accept(element->expr)->Print(std::cout);
  std::cout << std::endl;

  DEBUG_SINGLE((Accept(element->expr)->Print(debug_output()), ""))

  UnsetTosValue();
}

void Interpreter::Visit(std::shared_ptr<AssignmentStmt> element) {
  DEBUG_SINGLE(">>> Interpreter: AssignmentStmt")

  DEBUG_START 
    DEBUG("Is var") 
    DEBUG(element->lvalue->name)
    DEBUG("declared:")
    DEBUG((bool) current_scope_->IsDeclaredAnywhere(element->lvalue->name))
  DEBUG_FINISH
  for (auto& pr : current_scope_->GetVars()) {
    DEBUG_START DEBUG(pr.first.GetName()) DEBUG(pr.second) DEBUG_FINISH
  }

  auto value = Accept(element->expr);
  std::shared_ptr<Object> var = current_scope_->Get(element->lvalue->name);
  if (element->lvalue->expr) {  // arr[i] = x
    DEBUG_SINGLE(">>> Interpreter: Assignment subscript")
    DEBUG_SINGLE(var->IsArray())
    std::shared_ptr<Array> array = std::dynamic_pointer_cast<Array>(var);
    (*array)[Accept(element->lvalue->expr)->ToInt()] = value;
//    array->Print(std::cout);
//    DEBUG_SINGLE('\n')
  } else {  // a = b
    DEBUG_SINGLE(">>> Interpreter: Assignment no subscript")
    current_scope_->Set(element->lvalue->name, value);
//    current_scope_->Get(element->lvalue->name)->Print(std::cout);
//    DEBUG_SINGLE('\n')
  }
}

void Interpreter::Visit(std::shared_ptr<ReturnStmt> element) {
  DEBUG_SINGLE(">>> Interpreter: ReturnStmt")

  element->expr->Accept(shared_from_this());
  // TODO
}

void Interpreter::Visit(std::shared_ptr<MethodStmt> element) {
  DEBUG_SINGLE(">>> Interpreter: MethodStmt")

  element->invocation->Accept(shared_from_this());
  // TODO
}

void Interpreter::Visit(std::shared_ptr<BinOpExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: BinOpExpr")

  int lhs = Accept(element->lhs)->ToInt();
  int rhs = Accept(element->rhs)->ToInt();

  int tmp = 0;
  switch(element->op) {
    case BinOpExpr::Operation::OP_AND:     tmp = lhs && rhs; break;
    case BinOpExpr::Operation::OP_OR:      tmp = lhs || rhs; break;
    case BinOpExpr::Operation::OP_LESS:    tmp = lhs <  rhs; break;
    case BinOpExpr::Operation::OP_GREATER: tmp = lhs >  rhs; break;
    case BinOpExpr::Operation::OP_EQUAL:   tmp = lhs == rhs; break;
    case BinOpExpr::Operation::OP_PLUS:    tmp = lhs +  rhs; break;
    case BinOpExpr::Operation::OP_MINUS:   tmp = lhs -  rhs; break;
    case BinOpExpr::Operation::OP_STAR:    tmp = lhs *  rhs; break;
    case BinOpExpr::Operation::OP_SLASH:   tmp = lhs /  rhs; break;
    case BinOpExpr::Operation::OP_RMNDR:   tmp = lhs %  rhs; break;
    default: break;
  }

  SetTosValue(std::make_shared<Integer>(tmp));
}

void Interpreter::Visit(std::shared_ptr<SubscriptExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: SubscriptExpr")

  std::shared_ptr<Object> array = Accept(element->expr);
  SetTosValue(
    (*std::dynamic_pointer_cast<Array>(array))
      [Accept(element->idx)->ToInt()]
  );
}

void Interpreter::Visit(std::shared_ptr<LengthExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: LengthExpr")

  std::shared_ptr<Object> array = Accept(element->expr);
  SetTosValue(std::make_shared<Integer>(
        std::dynamic_pointer_cast<Array>(array)->GetLength()));
}

void Interpreter::Visit(std::shared_ptr<TrueExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: TrueExpr")

  SetTosValue(std::make_shared<Bool>(true));
}

void Interpreter::Visit(std::shared_ptr<FalseExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: FalseExpr")

  SetTosValue(std::make_shared<Bool>(false));
}

void Interpreter::Visit(std::shared_ptr<IntExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: IntExpr")

  SetTosValue(std::make_shared<Integer>(element->value));
}

void Interpreter::Visit(std::shared_ptr<NewExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: NewExpr")

  SetTosValue(std::make_shared<Class>(element->GetType().type));
}

void Interpreter::Visit(std::shared_ptr<NewArrayExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: NewArrayExpr")

  size_t len = Accept(element->expr)->ToInt();
  std::vector<std::shared_ptr<Object>> new_array;
  new_array.reserve(len);

  std::string type = element->type;
  if (type == "int") {
    for (size_t i = 0; i < len; ++i) {
      new_array.emplace_back(std::make_shared<Integer>(0));
    }
  } else if (type == "boolean") {
    for (size_t i = 0; i < len; ++i) {
      new_array.emplace_back(std::make_shared<Bool>(false));
    }
  } else if (type == "void") {
    // error thrown in symbol_tree_visitor_
  } else {
    for (size_t i = 0; i < len; ++i) {
      new_array.emplace_back(std::make_shared<Class>(type));
    }
  }

  SetTosValue(std::make_shared<Array>(type, new_array));
}

void Interpreter::Visit(std::shared_ptr<NotExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: NotExpr")

  SetTosValue(std::make_shared<Bool>(!Accept(element->expr)->ToBool()));
}

void Interpreter::Visit(std::shared_ptr<IdentExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: IdentExpr")

  DEBUG_SINGLE(current_scope_.current_child_index_)

  SetTosValue(current_scope_->Get(element->name));
}

void Interpreter::Visit(std::shared_ptr<MethodExpr> element) {
  DEBUG_SINGLE(">>> Interpreter: MethodExpr")

  element->invocation->Accept(shared_from_this());
  // TODO
}

void Interpreter::Visit(std::shared_ptr<ClassDecl> element) {
  DEBUG_SINGLE(">>> Interpreter: ClassDecl")

  current_scope_.GoDown();
  current_scope_.GoUp();
}

void Interpreter::Visit(std::shared_ptr<VarDecl> element) {
  DEBUG_SINGLE(">>> Interpreter: VarDecl")

  UnsetTosValue();
}

void Interpreter::Visit(std::shared_ptr<MethodDecl> element) {
  DEBUG_SINGLE(">>> Interpreter: MethodDecl")

  current_scope_.GoDown();
  current_scope_.GoUp();
}
 
void Interpreter::Visit(std::shared_ptr<Lvalue> element) {
  DEBUG_SINGLE(">>> Interpreter: Lvalue")

  // do nothing
}

void Interpreter::Visit(std::shared_ptr<MethodInvocation> element) {
  DEBUG_SINGLE(">>> Interpreter: MethodInvocation")

  // TODO
}

void Interpreter::SetTosValue(std::shared_ptr<Object> value){
  tos_value_ = value;
}

void Interpreter::UnsetTosValue(){
  tos_value_ = std::make_shared<Integer>(0);
}

int Interpreter::GetResult(std::shared_ptr<Program> program) {
  UnsetTosValue();
  Visit(program);

  return 0;
//  return tos_value_;
}

std::shared_ptr<Object> Interpreter::Accept(
    std::shared_ptr<BasicElement> element) {
  element->Accept(shared_from_this());
  return tos_value_;
}
