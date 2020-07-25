//
// Created by akhtyamovpavel on 4/8/20.
//

#include "utils/elements.hpp"
#include "irtree/elements.hpp"

#include "visitors/IrtreeBuildVisitor.hpp"
















IrtreeBuildVisitor::IrtreeBuildVisitor(const std::string& filename)
  : symbol_tree_visitor_{std::make_shared<SymbolTreeVisitor>(filename)},
    current_frame_{std::make_shared<IRT::FrameTranslator>("main")} {
}

IrtreeBuildVisitor::IrtreeBuildVisitor()
  : symbol_tree_visitor_{std::make_shared<SymbolTreeVisitor>()}, 
    current_frame_{std::make_shared<IRT::FrameTranslator>("main")} {
}







void IrtreeBuildVisitor::Visit(std::shared_ptr<Program> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: Program")

  // Build symbol tree
  symbol_tree_visitor_->Visit(element);
//  DEBUG_START DEBUG_FINISH DEBUG_START DEBUG_FINISH
  
  // Init tree
  tree_ = symbol_tree_visitor_->GetTree();

//  ScopeDown();

//  current_scope_->UnsetMain();
  element->class_decl_list->Accept(shared_from_this());

//  ScopeDown();
//  current_scope_->SetMain();
  element->main_class->Accept(shared_from_this());
//  ScopeUp();
}








void IrtreeBuildVisitor::Visit(std::shared_ptr<MainClass> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: MainClass")

  current_class_ = main_class_;
  current_frame_ = std::make_shared<IRT::FrameTranslator>("main");
  frame_translator_["main"] = current_frame_;
  VisitStmtList(element->stmt_list);
  method_trees_.emplace("main", tos_value_->ToStatement());
}







void IrtreeBuildVisitor::Visit(std::shared_ptr<AssertStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: AssertStmt")

  // TODO
  tos_value_ = nullptr;

  /*

  if (!Accept(element->expr)->ToBool()) {
    throw AssertExcepti1on();
  }
  */
}









void IrtreeBuildVisitor::Visit(std::shared_ptr<LocalVarDeclStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: LocalVarDeclStmt")

  element->var_decl->Accept(shared_from_this());
}









void IrtreeBuildVisitor::Visit(std::shared_ptr<StmtListStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: StmtListStmt")

  current_frame_->SetupScope();
  VisitStmtList(element->stmt_list);
  current_frame_->TearDownScope();
}








void IrtreeBuildVisitor::Visit(std::shared_ptr<IfStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: IfStmt")

  std::shared_ptr<IRT::SubtreeWrapper> expr = Accept(element->expr);

  current_frame_->SetupScope();
  std::shared_ptr<IRT::SubtreeWrapper> true_stmt = Accept(element->stmt);
  current_frame_->TearDownScope();

  IRT::Label label_true;
  IRT::Label label_join;

  IRT::Label* result_true = &label_join;
  IRT::Label* result_false = &label_join;

  std::shared_ptr<IRT::Statement> suffix = 
    std::make_shared<IRT::LabelStatement>(label_join);

  if (true_stmt) {
    result_true = &label_true;
    suffix = std::make_shared<IRT::SeqStatement>(
        std::make_shared<IRT::SeqStatement>(
          std::make_shared<IRT::LabelStatement>(label_true),
          
          true_stmt->ToStatement()),

        std::make_shared<IRT::LabelStatement>(label_join)
    );
  }

  tos_value_ = std::make_shared<IRT::StatementWrapper>(
      std::make_shared<IRT::SeqStatement>(
        expr->ToConditional(*result_true, *result_false),

        suffix
  ));
}







void IrtreeBuildVisitor::Visit(std::shared_ptr<IfElseStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: IfElseStmt")

  std::shared_ptr<IRT::SubtreeWrapper> expr = Accept(element->expr);

  current_frame_->SetupScope();
  auto true_stmt = Accept(element->stmt_true);
  current_frame_->TearDownScope();

  current_frame_->SetupScope();
  auto false_stmt = Accept(element->stmt_false);
  current_frame_->TearDownScope();

  IRT::Label label_true;
  IRT::Label label_false;
  IRT::Label label_join;

  IRT::Label* result_true = &label_join;
  IRT::Label* result_false = &label_join;

  std::shared_ptr<IRT::Statement> suffix =
    std::make_shared<IRT::LabelStatement>(label_join);

  if (false_stmt) {
    result_false = &label_false;
    suffix = std::make_shared<IRT::SeqStatement>(
        std::make_shared<IRT::LabelStatement>(label_false),

        std::make_shared<IRT::SeqStatement>(
          false_stmt->ToStatement(),

          suffix
    ));

    if (true_stmt) {
      suffix = std::make_shared<IRT::SeqStatement>(
          std::make_shared<IRT::JumpStatement>(label_join),

          suffix
      );
    }
  }

  if (true_stmt) {
    result_true = &label_true;
    suffix = std::make_shared<IRT::SeqStatement>(
        std::make_shared<IRT::LabelStatement>(label_true),

        std::make_shared<IRT::SeqStatement>(
          true_stmt->ToStatement(),

          suffix
    ));
  }

  tos_value_ = std::make_shared<IRT::StatementWrapper>(
      std::make_shared<IRT::SeqStatement>(
        expr->ToConditional(*result_true, *result_false),

        suffix
  ));
}







void IrtreeBuildVisitor::Visit(std::shared_ptr<WhileStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: WhileStmt")

  auto expr = Accept(element->expr);

  current_frame_->SetupScope();
  auto stmt = Accept(element->stmt);
  current_frame_->TearDownScope();

  IRT::Label label_cond;
  IRT::Label label_true;
  IRT::Label label_join;

  IRT::Label* result_true = &label_cond;
  IRT::Label* result_false = &label_join;

  auto suffix = std::make_shared<IRT::SeqStatement>(
      std::make_shared<IRT::JumpStatement>(label_cond),
      
      std::make_shared<IRT::LabelStatement>(label_join)
  );

  if (stmt) {
    result_true = &label_true;
    suffix = std::make_shared<IRT::SeqStatement>(
        std::make_shared<IRT::LabelStatement>(label_true),
        
        std::make_shared<IRT::SeqStatement>(
          stmt->ToStatement(),
          
          suffix
    ));
  }

  tos_value_ = std::make_shared<IRT::StatementWrapper>(
      std::make_shared<IRT::SeqStatement>(
        std::make_shared<IRT::LabelStatement>(label_cond),

        std::make_shared<IRT::SeqStatement>(
          expr->ToConditional(*result_true, *result_false),

        suffix 
  )));
}






void IrtreeBuildVisitor::Visit(std::shared_ptr<PrintStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: PrintStmt")

  auto expr_list = std::make_shared<IRT::ExpressionList>();
  expr_list->AddItem(Accept(element->expr)->ToExpression());

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
      std::make_shared<IRT::CallExpression>(
        std::make_shared<IRT::NameExpression>(IRT::Label("printf")),
        expr_list
  ));
}






void IrtreeBuildVisitor::Visit(std::shared_ptr<AssignmentStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: AssignmentStmt")

  auto lvalue = Accept(element->lvalue);
  auto rvalue = Accept(element->expr);

  tos_value_ = std::make_shared<IRT::StatementWrapper>(
      std::make_shared<IRT::MoveStatement>(
        lvalue->ToExpression(),
        rvalue->ToExpression()
  ));





/// XXX : DEPRECATED
/*

  DEBUG_START 
    DEBUG("Is var") 
    DEBUG(element->lvalue->name)
    DEBUG("declared:")
//  current_scope_ is "deprecated"
//    DEBUG((bool) current_scope_->IsDeclaredAnywhere(element->lvalue->name))
    DEBUG((bool) current_scope_->IsDeclared(element->lvalue->name))
  DEBUG_FINISH
//  current_scope_ is "deprecated"
//  for (auto& pr : current_scope_->GetVars()) {
//    DEBUG_START DEBUG(pr.first.GetName()) DEBUG(pr.second) DEBUG_FINISH
//  }

//#if DEBUG_ON
//  for (auto& symbol : function_table_->symbols_) {
//    DEBUG_START 
//      DEBUG(symbol.GetName())
//      DEBUG(function_table_->GetOffset(symbol))
//      DEBUG(current_frame_->GetValue(function_table_->GetOffset(symbol))
//    DEBUG_FINISH
//  }
//#endif

  // get value depending on class/main scope

  auto value = Accept(element->expr);
  std::shared_ptr<Object> var;
  Symbol symbol = Symbol(element->lvalue->name);

  if (!current_frame_->HasParent()) {
    size_t offset = function_table_->GetOffset(symbol);
    var = current_frame_->GetValue(offset);
  } else {
    if (current_scope_->IsArgument(symbol)) {
      var = current_frame_->GetValue(
          -current_scope_->GetArgIndex(symbol) - 2);
    } else if (current_scope_->IsClassData(symbol)) {
      auto This =
        std::dynamic_pointer_cast<Class>(current_frame_->GetValue(-1));
      DEBUG_SINGLE((This->Print(debug_output()), ""))

      var = This->GetValue(symbol);
    } else {
      size_t offset = function_table_->GetOffset(symbol);
      var = current_frame_->GetValue(offset);
    }
  }

  // assign depending on class/main scope and operands' type

  if (element->lvalue->expr) {  // arr[i] = x
    DEBUG_SINGLE(">>> IrtreeBuildVisitor: Assignment subscript")
    DEBUG_SINGLE(var->IsArray())
    std::shared_ptr<Array> array = std::dynamic_pointer_cast<Array>(var);
    (*array)[Accept(element->lvalue->expr)->ToInt()] = value;
//    array->Print(std::cout);
//    DEBUG_SINGLE('\n')
  } else {  // a = b
    DEBUG_SINGLE(">>> IrtreeBuildVisitor: Assignment no subscript")
    if (!current_frame_->HasParent()) {
      current_frame_->SetValue(
          function_table_->GetOffset(symbol),value);
    } else {
      if (current_scope_->IsArgument(symbol)) {
        if (var->IsClass()) {
          *var = *value;
        } else {
          current_frame_->SetValue(
              -current_scope_->GetArgIndex(symbol) - 2, value);
        }
      } else if (current_scope_->IsClassData(symbol)) {
        auto This =
          std::dynamic_pointer_cast<Class>(current_frame_->GetValue(-1));
        DEBUG_SINGLE((This->Print(debug_output()), ""))

        This->SetValue(symbol, value);
      } else {
        current_frame_->SetValue(
            function_table_->GetOffset(symbol), value);
      }
    }
//    current_scope_->Get(element->lvalue->name)->Print(std::cout);
//    DEBUG_SINGLE('\n')
  }

*/
/// XXX : DEPRECATED (end)


}








void IrtreeBuildVisitor::Visit(std::shared_ptr<ReturnStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: ReturnStmt")

  auto return_expr = Accept(element->expr);
  
  tos_value_ = std::make_shared<IRT::StatementWrapper>(
      std::make_shared<IRT::MoveStatement>(
        current_frame_->GetReturnValueAddress()->ToExpression(),
        return_expr->ToExpression()
  ));
}










void IrtreeBuildVisitor::Visit(std::shared_ptr<MethodStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: MethodStmt")

  tos_value_ = Accept(element->invocation);
}











void IrtreeBuildVisitor::Visit(std::shared_ptr<BinOpExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: BinOpExpr")

  auto lhs = Accept(element->lhs);
  auto rhs = Accept(element->rhs);

  std::shared_ptr<Expression> expr;

  switch(element->op) {
    case BinOpExpr::Operation::OP_AND:
      tos_value_ = 
        std::make_shared<IRT::AndConditionalWrapper>(lhs, rhs); break;
        
    case BinOpExpr::Operation::OP_OR:
      tos_value_ = 
        std::make_shared<IRT::OrConditionalWrapper>(lhs, rhs); break;

    case BinOpExpr::Operation::OP_LESS:
      tos_value_ = std::make_shared<IRT::RelativeConditionalWrapper>(
          IRT::LogicOperatorType::LT, 
          lhs->ToExpression(), 
          rhs->ToExpression()); break;
  
    case BinOpExpr::Operation::OP_GREATER:
      tos_value_ = std::make_shared<IRT::RelativeConditionalWrapper>(
          IRT::LogicOperatorType::GT, 
          lhs->ToExpression(), 
          rhs->ToExpression()); break;

    case BinOpExpr::Operation::OP_EQUAL:
      tos_value_ = std::make_shared<IRT::RelativeConditionalWrapper>(
          IRT::LogicOperatorType::EQ, 
          lhs->ToExpression(), 
          rhs->ToExpression()); break;

    case BinOpExpr::Operation::OP_PLUS:
      tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
          std::make_shared<IRT::BinopExpression>(
            IRT::BinaryOperatorType::PLUS,
            lhs->ToExpression(),
            rhs->ToExpression())); break;

    case BinOpExpr::Operation::OP_MINUS:
      tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
          std::make_shared<IRT::BinopExpression>(
            IRT::BinaryOperatorType::MINUS,
            lhs->ToExpression(),
            rhs->ToExpression())); break;

    case BinOpExpr::Operation::OP_STAR:
      tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
          std::make_shared<IRT::BinopExpression>(
            IRT::BinaryOperatorType::MUL,
            lhs->ToExpression(),
            rhs->ToExpression())); break;

    case BinOpExpr::Operation::OP_SLASH:
      tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
          std::make_shared<IRT::BinopExpression>(
            IRT::BinaryOperatorType::DIV,
            lhs->ToExpression(),
            rhs->ToExpression())); break;

    case BinOpExpr::Operation::OP_RMNDR:
      tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
          std::make_shared<IRT::BinopExpression>(
            IRT::BinaryOperatorType::MINUS,
            lhs->ToExpression(),
            std::make_shared<IRT::BinopExpression>(
              IRT::BinaryOperatorType::MUL,
              rhs->ToExpression(),
              std::make_shared<IRT::BinopExpression>(
                IRT::BinaryOperatorType::DIV,
                lhs->ToExpression(),
                rhs->ToExpression()
      )))); break;

    default: assert(false);
  }
}












void IrtreeBuildVisitor::Visit(std::shared_ptr<SubscriptExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: SubscriptExpr")
  
  auto var_expr = Accept(element->expr)->ToExpression();
  auto idx_expr = Accept(element->idx)->ToExpression();
  idx_expr = std::make_shared<IRT::BinopExpression>(
      IRT::BinaryOperatorType::PLUS,
      idx_expr,        
      // *(array+0) = array.length; ith element in *(array+i+1)
      std::make_shared<IRT::ConstExpression>(1));

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
      Subscript(var_expr, idx_expr));
}













void IrtreeBuildVisitor::Visit(std::shared_ptr<LengthExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: LengthExpr")

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
      std::make_shared<IRT::MemExpression>(
        Accept(element->expr)->ToExpression()
  ));
}













void IrtreeBuildVisitor::Visit(std::shared_ptr<TrueExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: TrueExpr")

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
      std::make_shared<IRT::ConstExpression>(1)
  );
}










void IrtreeBuildVisitor::Visit(std::shared_ptr<FalseExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: FalseExpr")

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
      std::make_shared<IRT::ConstExpression>(0)
  );
}










void IrtreeBuildVisitor::Visit(std::shared_ptr<IntExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: IntExpr")

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
      std::make_shared<IRT::ConstExpression>(element->value)
  );
}










void IrtreeBuildVisitor::Visit(std::shared_ptr<NewExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: NewExpr")

// TODO  SetTosValue(Constructor::GetInstance().Construct(element->GetType().type));

  std::string type = element->GetType().type;
  auto expr_list = std::make_shared<IRT::ExpressionList>();
  expr_list->AddItem(
      std::make_shared<IRT::ConstExpression>(
        std::make_shared<ClassBuilder>()->GetSize(type)
  ));

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
      std::make_shared<IRT::CallExpression>(
        std::make_shared<IRT::NameExpression>(IRT::Label("malloc")),
        expr_list
  ));
}











void IrtreeBuildVisitor::Visit(std::shared_ptr<NewArrayExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: NewArrayExpr")

  auto size = Accept(element->expr)->ToExpression();
  auto expr_list = std::make_shared<IRT::ExpressionList>();
  expr_list->AddItem(std::make_shared<IRT::BinopExpression>(
        IRT::BinaryOperatorType::MUL,
        size,
        std::make_shared<IRT::ConstExpression>(4/*word_size*/)
  ));

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
      std::make_shared<IRT::CallExpression>(
        std::make_shared<IRT::NameExpression>(IRT::Label("malloc")),
        expr_list
  ));

  /*
  size_t len = Accept(element->expr)->ToInt();
  std::vector<std::shared_ptr<Object>> new_array;
  new_array.reserve(len);

  std::string type = element->type;
  for (size_t i = 0; i < len; ++i) {
    new_array.emplace_back(Constructor::GetInstance().Construct(type));
  }

  SetTosValue(std::make_shared<Array>(type, new_array));
  */
}











void IrtreeBuildVisitor::Visit(std::shared_ptr<NotExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: NotExpr")

  tos_value_ = std::make_shared<IRT::NegateConditionalWrapper>(
      Accept(element->expr)
  );
}











void IrtreeBuildVisitor::Visit(std::shared_ptr<IdentExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: IdentExpr")

  Accept(std::make_shared<Lvalue>(element->name));

/* XXX : DEPRECATED

//  current_scope_ is "deprecated"
//  DEBUG_SINGLE(current_scope_.current_child_index_)


//  DEBUG_START 
//    DEBUG(element->name)
//    DEBUG(function_table_->GetOffset(Symbol(element->name)))
//    DEBUG(current_frame_->GetValue(function_table_->GetOffset(Symbol(element->name)))
//  DEBUG_FINISH


  std::shared_ptr<Object> value;
  Symbol symbol = Symbol(element->name);

  if (!current_frame_->HasParent()) {
    value = current_frame_->GetValue(function_table_->GetOffset(symbol));
  } else {
    if (current_scope_->IsArgument(symbol)) {
      value = current_frame_->GetValue(
          -current_scope_->GetArgIndex(symbol) - 2);
    } else if (current_scope_->IsClassData(symbol)) {
      auto This =
        std::dynamic_pointer_cast<Class>(current_frame_->GetValue(-1));
      DEBUG_SINGLE((This->Print(debug_output()), ""))

      value = This->GetValue(symbol);
    } else {
      size_t offset = function_table_->GetOffset(symbol);
      value = current_frame_->GetValue(function_table_->GetOffset(symbol));
    }
  }

  SetTosValue(value);

*/
 
  // XXX : DEPRECATED (end)
}









void IrtreeBuildVisitor::Visit(std::shared_ptr<MethodExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: MethodExpr")

  tos_value_ = Accept(element->invocation);
}











void IrtreeBuildVisitor::Visit(std::shared_ptr<ThisExpr> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: ThisExpr")

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
      current_frame_->GetThisAddress()->ToExpression()
  );
}










void IrtreeBuildVisitor::Visit(std::shared_ptr<ClassDecl> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: ClassDecl")

  current_class_ = element->class_name;
  element->decl_list->Accept(shared_from_this());
}








void IrtreeBuildVisitor::Visit(std::shared_ptr<VarDecl> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: VarDecl")

  if (current_class_ == main_class_ || method_decl_) {
    current_frame_->AddLocalVariable(element->name);
  }
  tos_value_ = nullptr;
}









void IrtreeBuildVisitor::Visit(std::shared_ptr<MethodDecl> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: MethodDecl")

  // build new frame
  std::string func_name = current_class_ + "::" + element->name;
  current_frame_ = std::make_shared<IRT::FrameTranslator>(func_name);
  frame_translator_[func_name] = current_frame_;

  current_frame_->AddThisAddress();
  for (auto&& arg_name : element->function_type.arg_names) {
    current_frame_->AddArgumentAddress(arg_name);
  }
  current_frame_->AddReturnAddress();

  method_decl_ = true;
  VisitStmtList(element->stmt_list);
  method_decl_ = false;
  auto statements_ir = tos_value_;


  if (statements_ir) {
    tos_value_ = std::make_shared<IRT::StatementWrapper>(
        std::make_shared<IRT::SeqStatement>(
          std::make_shared<IRT::LabelStatement>(
            IRT::Label(func_name)),
          statements_ir->ToStatement() 
          // TODO: set return value 0 by default
    ));
  } else {
    // generating return 0
    tos_value_ = std::make_shared<IRT::StatementWrapper>(
        std::make_shared<IRT::SeqStatement>(
          std::make_shared<IRT::LabelStatement>(
            IRT::Label(func_name)),
          std::make_shared<IRT::MoveStatement>(
            current_frame_->GetReturnValueAddress()->ToExpression(),
            std::make_shared<IRT::ConstExpression>(0)
    )));
  }

//   will it work without emplace?..
  method_trees_.emplace(func_name, tos_value_->ToStatement());
//  method_trees_[element->name] = tos_value_->ToStatement();
}











void IrtreeBuildVisitor::Visit(std::shared_ptr<Lvalue> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: Lvalue")

  auto fields = 
    std::make_shared<ClassBuilder>()->GetClassFields(current_class_);
  std::shared_ptr<IRT::Expression> var_expr;

  // check if class field
  if (current_class_ == main_class_ ||
      fields.find(element->name) == fields.end()) {
    var_expr = current_frame_->GetAddress(element->name)->ToExpression();
  } else {
    auto this_expr = current_frame_->GetThisAddress()->ToExpression();
    var_expr = Subscript(this_expr, 
        std::make_shared<IRT::ConstExpression>(
          std::make_shared<ClassBuilder>()->GetFieldIndex(
            current_class_, element->name)));
  }

  // check if subscription
  auto expr = var_expr;
  if (element->expr) {
    auto idx_expr = Accept(element->expr)->ToExpression();
    idx_expr = std::make_shared<IRT::BinopExpression>(
        IRT::BinaryOperatorType::PLUS,
        idx_expr,        
        // *(array+0) = array.length; ith element in *(array+i+1)
        std::make_shared<IRT::ConstExpression>(1));
    expr = Subscript(var_expr, idx_expr);
  }

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(expr);
  


/*

  auto var_addr = std::dynamic_pointer_cast<IRT::AddressInFrame>(
      current_frame_->GetAddress(element->name));

  std::shared_ptr<IRT::Expression> offset_expr =
    std::make_shared<IRT::ConstExpression>(0);

  // if class data: add offset
  // TODO

  // if array: add offset
  if (element->expr) {
    var_addr->AddOffset(
        std::make_shared<IRT::BinopExpression>(
          IRT::BinaryOperatorType::MUL,
          
          std::make_shared<IRT::BinopExpression>(
            IRT::BinaryOperatorType::PLUS,
            Accept(element->expr)->ToExpression(),
            
            // *(array+0) = array.length; ith element in *(array+i+1)
            std::make_shared<IRT::ConstExpression>(1)),
          
          std::make_shared<IRT::ConstExpression>(4word_size)
    ));
  }

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
      var_addr->ToExpression());
*/
}











void IrtreeBuildVisitor::Visit(std::shared_ptr<MethodInvocation> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: MethodInvocation")

  auto args_list = std::make_shared<IRT::ExpressionList>();

  args_list->AddItem(Accept(element->expr)->ToExpression());
  for (auto&& it : element->comma_expr_list->items) {
    args_list->AddItem(Accept(it)->ToExpression());
  }

  tos_value_ = std::make_shared<IRT::ExpressionWrapper>(
    std::make_shared<IRT::CallExpression>(
      std::make_shared<IRT::NameExpression>(IRT::Label(
          element->expr->GetType().type + "::" + element->func_name)),
      args_list
    )
  );






  /*

  auto function = FunctionStorage::GetInstance().GetFunction(
      element->expr->GetType().type, element->func_name);
  auto function_type = function->function_type;

  // make child frame
  auto new_frame = std::make_shared<Frame>(function_type);
  new_frame->SetParent(current_frame_);

  // set args
  new_frame->SetValue(-1, Accept(element->expr));
  for (size_t i = 0; i < function_type.GetNumArgs(); ++i) {
    new_frame->SetValue(-i - 2, Accept((*element->comma_expr_list)[i]));
  }

  // precall
  current_frame_ = new_frame;
  
  ScopeDown();
  DEBUG_SINGLE("Method invocation: link function")
  current_scope_->AddChild(
      symbol_tree_visitor_->GetTree()->GetFunctionScope(
        new_frame->GetValue(-1)->GetType().type, element->func_name));
  DEBUG_SINGLE("Method invocation: link function (end)")
  ScopeDown();
  current_scope_->UnsetMain();

  // call
  for (size_t i = 0; i < function->stmt_list->GetLength(); ++i) {
    if (!current_frame_->IsReturned()) {
      (*function->stmt_list)[i]->Accept(shared_from_this());
    }
  }

  // ret
  ScopeUp();
  ScopeUp();

  // postret
  current_frame_ = current_frame_->GetParent();
  tos_value_ = current_frame_->GetReturnValue();

  */
}












std::shared_ptr<IRT::SubtreeWrapper> IrtreeBuildVisitor::Accept(
    std::shared_ptr<BasicElement> element) {
  element->Accept(shared_from_this());
  return tos_value_;
}










// XXX: deprecated
  /*
void IrtreeBuildVisitor::ScopeDown() {
  auto new_current_scope = current_scope_;
  new_current_scope.GoDown();
  new_current_scope.GoUp();
  scope_stack_.push(new_current_scope);

  current_scope_.GoDown();
  current_frame_->AllocScope();
  function_table_->BeginScope();
}
  */










// XXX: deprecated
  /*
void IrtreeBuildVisitor::ScopeUp() {
  current_scope_ = scope_stack_.top();
  scope_stack_.pop();

  current_frame_->DeallocScope();
  function_table_->EndScope();
}
  */






/*



void IrtreeBuildVisitor::Visit(ParamList *param_list) {
  for (auto param: param_list->params_) {
    current_frame_->AddArgumentAddress(param);
  }
}






void IrtreeBuildVisitor::Visit(Function *function) {
  // build new frame
  current_frame_ = new IRT::FrameTranslator(function->name_);
  frame_translator_[function->name_] = current_frame_;

  function->param_list_->Accept(this);

  current_frame_->AddReturnAddress();

  auto statements_ir = Accept(function->statements_);

  if (statements_ir) {

    tos_value_ = new IRT::StatementWrapper(
        new IRT::SeqStatement(
            new IRT::LabelStatement(IRT::Label(function->name_)),
            statements_ir->ToStatement() // TODO: set return value 0 by default
        )
    );
  } else {
    // generating return 0
    tos_value_ = new IRT::StatementWrapper(
      new IRT::SeqStatement(
        new IRT::LabelStatement(IRT::Label(function->name_)),
        new IRT::MoveStatement(
            current_frame_->GetReturnValueAddress()->ToExpression(),
            new IRT::ConstExpression(0)
        )
      )
    );
  }

  method_trees_.emplace(function->name_, tos_value_->ToStatement());
}






void IrtreeBuildVisitor::Visit(FunctionCallExpression *statement) {
  IRT::ExpressionList* irt_expressions = new IRT::ExpressionList();

  for (auto it: statement->param_list_->params_) {
    irt_expressions->Add(Accept(it)->ToExpression());
  }

  tos_value_ = new IRT::ExpressionWrapper(
    new IRT::CallExpression(
        new IRT::NameExpression(IRT::Label(statement->name_)),
        irt_expressions
    )
  );

}








void IrtreeBuildVisitor::Visit(FunctionList *function_list) {
  for (auto function: function_list->functions_) {
    function->Accept(this);
  }
}





void IrtreeBuildVisitor::Visit(ParamValueList *value_list) {

}




void IrtreeBuildVisitor::Visit(ReturnStatement *return_statement) {
  auto return_expr = Accept(return_statement->return_expression_);
  tos_value_ = new IRT::StatementWrapper(
      new IRT::MoveStatement(
        current_frame_->GetReturnValueAddress()->ToExpression(),
        return_expr->ToExpression()
      )
  );
}






void IrtreeBuildVisitor::Visit(AndExpression *and_expression) {
  auto first_wrapper = Accept(and_expression->first);
  auto second_wrapper = Accept(and_expression->second);

  tos_value_ = new IRT::AndConditionalWrapper(
      first_wrapper,
      second_wrapper
  );
}




void IrtreeBuildVisitor::Visit(OrExpression *or_expression) {
  auto first_wrapper = Accept(or_expression->first);
  auto second_wrapper = Accept(or_expression->second);

  tos_value_ = new IRT::OrConditionalWrapper(
    first_wrapper,
    second_wrapper
  );
}





void IrtreeBuildVisitor::Visit(NotExpression *not_expression) {
  auto wrapper = Accept(not_expression->expression_);

  tos_value_ = new IRT::NegateConditionalWrapper(
      wrapper
  );
}





void IrtreeBuildVisitor::Visit(IfStatement *if_statement) {
  auto if_cond_expression = Accept(if_statement->bool_expression_);
  current_frame_->SetupScope();
  auto true_stmt = Accept(if_statement->true_statement_);
  current_frame_->TearDownScope();
  current_frame_->SetupScope();
  auto false_stmt = Accept(if_statement->false_statement_);
  current_frame_->TearDownScope();

  IRT::Label label_true;
  IRT::Label label_false;
  IRT::Label label_join;

  IRT::Statement* suffix = new IRT::LabelStatement(label_join);

  IRT::Label* result_true = &label_join;
  IRT::Label* result_false = &label_join;

  if (false_stmt) {
    result_false = &label_false;
    suffix = new IRT::SeqStatement(
        new IRT::LabelStatement(label_false),
        new IRT::SeqStatement(false_stmt->ToStatement(), suffix)
    );

    if (true_stmt) {
      suffix = new IRT::SeqStatement(
        new IRT::JumpStatement(label_join),
        suffix
      );
    }
  }

  if (true_stmt) {
    result_true = &label_true;
    suffix = new IRT::SeqStatement(
      new IRT::LabelStatement(label_true),
      new IRT::SeqStatement(true_stmt->ToStatement(), suffix)
    );
  }

  tos_value_ = new IRT::StatementWrapper(
    new IRT::SeqStatement(
      if_cond_expression->ToConditional(*result_true, *result_false),
      suffix
    )
  );
}







void IrtreeBuildVisitor::Visit(GtExpression *gt_expression) {
  tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::GT,
      Accept(gt_expression->first)->ToExpression(),
      Accept(gt_expression->second)->ToExpression()
  );
}








void IrtreeBuildVisitor::Visit(LtExpression *lt_expression) {
  tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::LT,
      Accept(lt_expression->first)->ToExpression(),
      Accept(lt_expression->second)->ToExpression()
  );
}








IrtreeBuildVisitor::IrtreeBuildVisitor(ScopeLayerTree *layer_tree): tree_(layer_tree) {
  // We don't need symbol table but you need with type system
  // Our functions return one type and operate with one type
}
*/

void IrtreeBuildVisitor::VisitStmtList(std::shared_ptr<BasicList> element) {
  std::vector<std::shared_ptr<IRT::Statement>> statements;
  for (auto&& statement : element->items) {
    auto stmt = Accept(statement);
    if (stmt) {
      statements.push_back(stmt->ToStatement());
    }
  }

  if (statements.size() == 0) {
    tos_value_ = nullptr;
    return;
  }

  if (statements.size() == 1) {
    tos_value_ = std::make_shared<IRT::StatementWrapper>(statements[0]);
    return;
  }  

  std::shared_ptr<IRT::Statement> suffix = statements.back();
  for (auto it = ++statements.rbegin(); it != statements.rend(); ++it) {
    suffix = std::make_shared<IRT::SeqStatement>(
        *it,
        suffix
    );
  }

  tos_value_ = std::make_shared<IRT::StatementWrapper>(suffix);
}

IrtMapping IrtreeBuildVisitor::GetTrees() {
  return method_trees_;
}


std::shared_ptr<IRT::Expression> IrtreeBuildVisitor::Subscript(
    std::shared_ptr<IRT::Expression> var_expr,
    std::shared_ptr<IRT::Expression> idx_expr) const {
  DEBUG_SINGLE("IRTree::Subscript")
  
  std::shared_ptr<IRT::Expression> offset_expr = 
    std::make_shared<IRT::BinopExpression>(
        IRT::BinaryOperatorType::MUL,
        
        idx_expr,
        std::make_shared<IRT::ConstExpression>(4/*word_size*/)
  );

  return std::make_shared<IRT::MemExpression>(
      std::make_shared<IRT::BinopExpression>(
        IRT::BinaryOperatorType::PLUS,
        var_expr,
        offset_expr));
}


