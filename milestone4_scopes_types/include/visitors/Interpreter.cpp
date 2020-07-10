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
  DEBUG("Program")

  // Build symbol tree
  symbol_tree_visitor_->Visit(element);
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
  DEBUG("MainClass")

  element->stmt_list->Accept(shared_from_this());
}

void Interpreter::Visit(std::shared_ptr<AssertStmt> element) {
  DEBUG("AssertStmt")

  if (!Accept(element->expr)->ToBool()) {
    throw AssertException();
  }
}

void Interpreter::Visit(std::shared_ptr<LocalVarDeclStmt> element) {
  DEBUG("LocalVarDeclStmt")

  element->var_decl->Accept(shared_from_this());
}

void Interpreter::Visit(std::shared_ptr<StmtListStmt> element) {
  DEBUG("StmtListStmt")

  current_scope_.GoDown();
  element->stmt_list->Accept(shared_from_this());
  current_scope_.GoUp();
}

void Interpreter::Visit(std::shared_ptr<IfStmt> element) {
  DEBUG("IfStmt")

  if (Accept(element->expr)->ToBool()) { 
    element->stmt->Accept(shared_from_this()); 
  }
}

void Interpreter::Visit(std::shared_ptr<IfElseStmt> element) {
  DEBUG("IfElseStmt")

  if (Accept(element->expr)->ToBool()) { 
    tos_value_ = Accept(element->stmt_true);
  } else {
    tos_value_ = Accept(element->stmt_false);
  }
}

void Interpreter::Visit(std::shared_ptr<WhileStmt> element) {
  DEBUG("WhileStmt")

  auto old_current_scope = current_scope_;
  auto new_current_scope = current_scope_;

  while (Accept(element->expr)->ToBool()) {
    element->stmt->Accept(shared_from_this()); 

    new_current_scope = current_scope_;
    current_scope_ = old_current_scope;
  }
  current_scope_ = new_current_scope;
}

void Interpreter::Visit(std::shared_ptr<PrintStmt> element) {
  DEBUG("PrintStmt")

  Accept(element->expr)->Print(std::cout);
  std::cout << std::endl;
  UnsetTosValue();
}

void Interpreter::Visit(std::shared_ptr<AssignmentStmt> element) {
  DEBUG("AssignmentStmt")

  auto value = Accept(element->expr);
  std::shared_ptr<Object> var = current_scope_->Get(element->lvalue->name);
  if (element->lvalue->expr) {  // arr[i] = x
    DEBUG("Assignment subscript")
    DEBUG(var->IsArray())
    std::shared_ptr<Array> array = std::dynamic_pointer_cast<Array>(var);
    (*array)[Accept(element->lvalue->expr)->ToInt()] = value;
//    array->Print(std::cout);
//    DEBUG('\n')
  } else {  // a = b
    DEBUG("Assignment no subscript")
    current_scope_->Set(element->lvalue->name, value);
//    current_scope_->Get(element->lvalue->name)->Print(std::cout);
//    DEBUG('\n')
  }
}

void Interpreter::Visit(std::shared_ptr<BinOpExpr> element) {
  DEBUG("BinOpExpr")

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
  DEBUG("SubscriptExpr")

  std::shared_ptr<Object> array = Accept(element->expr);
  SetTosValue(
    (*std::dynamic_pointer_cast<Array>(array))
      [Accept(element->idx)->ToInt()]
  );
}

void Interpreter::Visit(std::shared_ptr<LengthExpr> element) {
  DEBUG("LengthExpr")

  std::shared_ptr<Object> array = Accept(element->expr);
  SetTosValue(std::make_shared<Integer>(
        std::dynamic_pointer_cast<Array>(array)->GetLength()));
}

void Interpreter::Visit(std::shared_ptr<TrueExpr> element) {
  DEBUG("TrueExpr")

  SetTosValue(std::make_shared<Bool>(true));
}

void Interpreter::Visit(std::shared_ptr<FalseExpr> element) {
  DEBUG("FalseExpr")

  SetTosValue(std::make_shared<Bool>(false));
}

void Interpreter::Visit(std::shared_ptr<IntExpr> element) {
  DEBUG("IntExpr")

  SetTosValue(std::make_shared<Integer>(element->value));
}

void Interpreter::Visit(std::shared_ptr<NewExpr> element) {
  DEBUG("NewExpr")

  SetTosValue(std::make_shared<Class>(element->GetType().type));
}

void Interpreter::Visit(std::shared_ptr<NewArrayExpr> element) {
  DEBUG("NewArrayExpr")

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
  DEBUG("NotExpr")

  SetTosValue(std::make_shared<Bool>(!Accept(element->expr)->ToBool()));
}

void Interpreter::Visit(std::shared_ptr<IdentExpr> element) {
  DEBUG("IdentExpr")

  SetTosValue(current_scope_->Get(element->name));
}

void Interpreter::Visit(std::shared_ptr<ClassDecl> element) {
  DEBUG("ClassDecl")

  current_scope_.GoDown();
  current_scope_.GoUp();
}

void Interpreter::Visit(std::shared_ptr<VarDecl> element) {
  DEBUG("VarDecl")

  UnsetTosValue();
}
 
void Interpreter::Visit(std::shared_ptr<Lvalue> element) {
  DEBUG("Lvalue")

  // do nothing
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
