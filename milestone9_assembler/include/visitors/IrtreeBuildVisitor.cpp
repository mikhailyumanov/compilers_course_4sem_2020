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
  
  // Init tree
  tree_ = symbol_tree_visitor_->GetTree();

  element->class_decl_list->Accept(shared_from_this());

  element->main_class->Accept(shared_from_this());
}

void IrtreeBuildVisitor::Visit(std::shared_ptr<MainClass> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: MainClass")

  current_class_ = main_class_;
  current_frame_ = std::make_shared<IRT::FrameTranslator>("main");
  frame_translator_["main"] = current_frame_;
  VisitStmtList(element->stmt_list);
  method_trees_["main"] = tos_value_->ToStatement();
}

void IrtreeBuildVisitor::Visit(std::shared_ptr<AssertStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: AssertStmt")

  // TODO
  tos_value_ = nullptr;
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
}

void IrtreeBuildVisitor::Visit(std::shared_ptr<ReturnStmt> element) {
  DEBUG_SINGLE(">>> IrtreeBuildVisitor: ReturnStmt")

  auto return_expr = Accept(element->expr);
  
  tos_value_ = std::make_shared<IRT::StatementWrapper>(
      std::make_shared<IRT::MoveStatement>(
        current_frame_->GetReturnValueAddress()->ToExpression(),
        return_expr->ToExpression())
  );
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

  method_trees_[element->name] = tos_value_->ToStatement();
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
}

std::shared_ptr<IRT::SubtreeWrapper> IrtreeBuildVisitor::Accept(
    std::shared_ptr<BasicElement> element) {
  element->Accept(shared_from_this());
  return tos_value_;
}

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
