#include "irtree/visitors/EseqEliminationVisitor.hpp"

#include <cassert>


namespace IRT {

EseqEliminationVisitor::EseqEliminationVisitor()
  : ident_visitor_{std::make_shared<IdentVisitor>()} {
}

void EseqEliminationVisitor::Visit(std::shared_ptr<ExpStatement> element) {
  DEBUG_SINGLE("EseqElimination::ExpStatement")

  auto expr = Accept(element->GetExpression()).expr;
  element->SetExpression(expr);

  DEBUG_SINGLE("exp stmt: pre `is eseq`")
  std::shared_ptr<IRT::Statement> tmp = element;
  if (IsEseq(expr)) {
    tmp = std::dynamic_pointer_cast<IRT::EseqExpression>(expr)->stmt;
  }

  tos_value_.stmt = tmp;
  
  DEBUG_SINGLE("EseqElimination::ExpStatement (finish)")
}

void EseqEliminationVisitor::Visit(
    std::shared_ptr<JumpConditionalStatement> element) {
  DEBUG_SINGLE("EseqElimination::JumpConditionalStatement")

  auto lhs = Accept(element->lhs).expr;
  auto rhs = Accept(element->rhs).expr;
  element->lhs = lhs;
  element->rhs = rhs;

  bool is_lhs_eseq = IsEseq(lhs);
  bool is_rhs_eseq = IsEseq(rhs);

  std::shared_ptr<IRT::Statement> tmp;
  if (is_lhs_eseq && !is_rhs_eseq) {
    DEBUG_SINGLE("cjump: is_lhs_eseq && !is_rhs_eseq")

    auto eseq = std::dynamic_pointer_cast<IRT::EseqExpression>(element->lhs);
    tmp = std::make_shared<IRT::SeqStatement>(
        eseq->stmt,
        std::make_shared<IRT::JumpConditionalStatement>(
          element->operator_type,
          eseq->expr,
          element->rhs,
          element->label_true,
          element->label_false));

  } else if (!is_lhs_eseq && is_rhs_eseq) {
    DEBUG_SINGLE("cjump: !is_lhs_eseq && is_rhs_eseq")

    Temporary t;
    auto eseq = std::dynamic_pointer_cast<IRT::EseqExpression>(element->rhs);
    tmp = std::make_shared<IRT::SeqStatement>(
        std::make_shared<IRT::MoveStatement>(
          std::make_shared<IRT::TempExpression>(t),
          element->lhs),

        std::make_shared<IRT::SeqStatement>(
          eseq->stmt,

          std::make_shared<IRT::JumpConditionalStatement>(
            element->operator_type,
            std::make_shared<IRT::TempExpression>(t),
            element->rhs,
            element->label_true,
            element->label_false)));

  } else if (is_lhs_eseq && is_rhs_eseq) {
    DEBUG_SINGLE("cjump: is_lhs_eseq && is_rhs_eseq")

    Temporary t;
    auto eseq_lhs = std::dynamic_pointer_cast<IRT::EseqExpression>(
        element->lhs);
    auto eseq_rhs = std::dynamic_pointer_cast<IRT::EseqExpression>(
        element->rhs);

    tmp = std::make_shared<IRT::SeqStatement>(
        eseq_lhs->stmt,

        std::make_shared<IRT::SeqStatement>(
          std::make_shared<IRT::MoveStatement>(
            std::make_shared<IRT::TempExpression>(t),
            eseq_lhs->expr),
          
          std::make_shared<IRT::SeqStatement>(
            eseq_rhs->stmt,
            
            std::make_shared<IRT::JumpConditionalStatement>(
              element->operator_type,
              std::make_shared<IRT::TempExpression>(t),
              eseq_rhs->expr,
              element->label_true,
              element->label_false))));

  } else {
    DEBUG_SINGLE("cjump: !is_lhs_eseq && !is_rhs_eseq")

    tmp = element;
  }

  tos_value_.stmt = tmp;
  
  DEBUG_SINGLE("EseqElimination::JumpConditionalStatement (finish)")
}

void EseqEliminationVisitor::Visit(std::shared_ptr<MoveStatement> element) {
  DEBUG_SINGLE("EseqElimination::MoveStatement")

  auto target = Accept(element->target).expr;
  auto source = Accept(element->source).expr;
  element->target = target;
  element->source = source;

  bool is_target_eseq = IsEseq(target);
  bool is_source_eseq = IsEseq(source);

  std::shared_ptr<IRT::Statement> tmp;
  if (is_target_eseq && !is_source_eseq) {
    DEBUG_SINGLE("move: is_target_eseq && !is_source_eseq")

    auto eseq = std::dynamic_pointer_cast<IRT::EseqExpression>(
        element->target);
    tmp = std::make_shared<IRT::SeqStatement>(
        eseq->stmt,

        std::make_shared<IRT::MoveStatement>(
          eseq->expr,
          element->source));

  } else if (!is_target_eseq && is_source_eseq) {
    DEBUG_SINGLE("move: !is_target_eseq && is_source_eseq")

    auto eseq = std::dynamic_pointer_cast<IRT::EseqExpression>(
          element->source);
    if (ident_visitor_->Accept(element->target) == NodeType::TempExpression) {
      DEBUG_SINGLE("move: target is temp")

      tmp = std::make_shared<IRT::SeqStatement>(
          eseq->stmt,
          std::make_shared<IRT::MoveStatement>(
            element->target,
            eseq->expr));
    } else { // element->target is MemExpression
      DEBUG_SINGLE("move: target is MemExpr")

      Temporary t;
      auto mem_expr = std::dynamic_pointer_cast<IRT::MemExpression>(
          element->target);
      tmp = std::make_shared<IRT::SeqStatement>(
          std::make_shared<IRT::MoveStatement>(
            std::make_shared<IRT::TempExpression>(t),
            mem_expr->expr),
          
          std::make_shared<IRT::SeqStatement>(
            eseq->stmt,
            
            std::make_shared<IRT::MoveStatement>(
              std::make_shared<IRT::MemExpression>(
                std::make_shared<IRT::TempExpression>(t)),
              eseq->expr)));
    }
    
  } else if (is_target_eseq && is_source_eseq) {
    DEBUG_SINGLE("move: is_target_eseq && is_source_eseq")

    auto eseq_target = std::dynamic_pointer_cast<IRT::EseqExpression>(
        element->target);
    auto eseq_source = std::dynamic_pointer_cast<IRT::EseqExpression>(
        element->source);

    if (ident_visitor_->Accept(element->target) == NodeType::TempExpression) {
      DEBUG_SINGLE("move: target is temp")

      tmp = std::make_shared<IRT::SeqStatement>(
          eseq_target->stmt,
          
          std::make_shared<IRT::SeqStatement>(
            eseq_source->stmt,
            
            std::make_shared<IRT::MoveStatement>(
              eseq_target->expr,
              eseq_source->expr)));
    } else { // element->target is MemExpression
      DEBUG_SINGLE("move: target is MemExpr")

      Temporary t;
      auto mem_expr = std::dynamic_pointer_cast<IRT::MemExpression>(
          eseq_target->expr);
      tmp = std::make_shared<IRT::SeqStatement>(
          eseq_target->stmt,
          
          std::make_shared<IRT::SeqStatement>(
            std::make_shared<IRT::MoveStatement>(
              std::make_shared<IRT::TempExpression>(t),
              mem_expr->expr),

            std::make_shared<IRT::SeqStatement>(
              eseq_source->stmt,
              
              std::make_shared<IRT::MoveStatement>(
                std::make_shared<IRT::MemExpression>(
                  std::make_shared<IRT::TempExpression>(t)),
                eseq_source->expr))));
    }

  } else {
    DEBUG_SINGLE("move: !is_target_eseq && !is_source_eseq")

    tmp = element;
  }

  tos_value_.stmt = tmp;

  DEBUG_SINGLE("EseqElimination::MoveStatement (finish)")
}

void EseqEliminationVisitor::Visit(std::shared_ptr<SeqStatement> element) {
  DEBUG_SINGLE("EseqElimination::SeqStatement")

  auto lhs = Accept(element->lhs).stmt;
  auto rhs = Accept(element->rhs).stmt;
  element->lhs = lhs;
  element->rhs = rhs;

  tos_value_.stmt = element;

  DEBUG_SINGLE("EseqElimination::SeqStatement (finish)")
}

void EseqEliminationVisitor::Visit(std::shared_ptr<LabelStatement> element) {
  DEBUG_SINGLE("EseqElimination::LabelStatement")

  tos_value_.stmt = element;
}

void EseqEliminationVisitor::Visit(std::shared_ptr<JumpStatement> element) {
  DEBUG_SINGLE("EseqElimination::JumpStatement")

  tos_value_.stmt = element;
}

void EseqEliminationVisitor::Visit(std::shared_ptr<ConstExpression> element) {
  DEBUG_SINGLE("EseqElimination::ConstExpression")

  tos_value_.expr = element;
}

void EseqEliminationVisitor::Visit(std::shared_ptr<BinopExpression> element) {
  DEBUG_SINGLE("EseqElimination::BinopExpression")

  auto lhs = Accept(element->lhs).expr;
  auto rhs = Accept(element->rhs).expr;
  element->lhs = lhs;
  element->rhs = rhs;

  bool is_lhs_eseq = IsEseq(lhs);
  bool is_rhs_eseq = IsEseq(rhs);

  std::shared_ptr<IRT::Expression> tmp;
  if (is_lhs_eseq && !is_rhs_eseq) {
    DEBUG_SINGLE("binop: is_lhs_eseq && !is_rhs_eseq")

    auto eseq = std::dynamic_pointer_cast<IRT::EseqExpression>(element->lhs);
    tmp = std::make_shared<IRT::EseqExpression>(
        eseq->stmt,
        std::make_shared<IRT::BinopExpression>(
          element->operator_type,
          eseq->expr,
          element->rhs));

  } else if (!is_lhs_eseq && is_rhs_eseq) {
    DEBUG_SINGLE("binop: !is_lhs_eseq && is_rhs_eseq")
      
    Temporary t;
    auto eseq = std::dynamic_pointer_cast<IRT::EseqExpression>(element->rhs);
    tmp = std::make_shared<IRT::EseqExpression>(
        std::make_shared<IRT::MoveStatement>(
          std::make_shared<IRT::TempExpression>(t),
          element->lhs),

        std::make_shared<IRT::EseqExpression>(
          eseq->stmt,

          std::make_shared<IRT::BinopExpression>(
            element->operator_type,
            std::make_shared<IRT::TempExpression>(t),
            element->rhs)));
    Rehang(std::dynamic_pointer_cast<IRT::EseqExpression>(tmp));

  } else if (is_lhs_eseq && is_rhs_eseq) {
    DEBUG_SINGLE("binop: is_lhs_eseq && is_rhs_eseq")

    Temporary t;
    auto eseq_lhs = std::dynamic_pointer_cast<IRT::EseqExpression>(
        element->lhs);
    auto eseq_rhs = std::dynamic_pointer_cast<IRT::EseqExpression>(
        element->rhs);

    tmp = std::make_shared<IRT::EseqExpression>(
        eseq_lhs->stmt,

        std::make_shared<IRT::EseqExpression>(
          std::make_shared<IRT::SeqStatement>(
            std::make_shared<IRT::MoveStatement>(
              std::make_shared<IRT::TempExpression>(t),
              eseq_lhs->expr),
            eseq_rhs->stmt),
            
            std::make_shared<IRT::BinopExpression>(
              element->operator_type,
              std::make_shared<IRT::TempExpression>(t),
              eseq_rhs->expr)));
    Rehang(std::dynamic_pointer_cast<IRT::EseqExpression>(tmp));

  } else {
    DEBUG_SINGLE("binop: !is_lhs_eseq && !is_rhs_eseq")

    tmp = element;
  }

  tos_value_.expr = tmp;

  DEBUG_SINGLE("EseqElimination::BinopExpression (finish)")
}

void EseqEliminationVisitor::Visit(std::shared_ptr<TempExpression> element) {
  DEBUG_SINGLE("EseqElimination::TempExpression")

  tos_value_.expr = element;
}

void EseqEliminationVisitor::Visit(std::shared_ptr<MemExpression> element) {
  DEBUG_SINGLE("EseqElimination::MemExpression")

  auto expr = Accept(element->expr).expr;
  element->expr = expr;

  std::shared_ptr<IRT::Expression> tmp;
  if (IsEseq(expr)) {
    auto eseq = std::dynamic_pointer_cast<IRT::EseqExpression>(element->expr);
    tmp = std::make_shared<IRT::EseqExpression>(
        eseq->stmt,
        std::make_shared<IRT::MemExpression>(
          eseq->expr));
  } else {
    tmp = element;
  }

  tos_value_.expr = tmp;

  DEBUG_SINGLE("EseqElimination::MemExpression (finish)")
}

void EseqEliminationVisitor::Visit(std::shared_ptr<CallExpression> element) {
  DEBUG_SINGLE("EseqElimination::CallExpression")

  element->function_name->Accept(shared_from_this());
  element->args->Accept(shared_from_this());

  std::vector<size_t> eseq_indexes;
  auto& expr_list = element->args->expr_list;

  for (size_t i = 0; i < expr_list.size(); ++i) {
    if (IsEseq(expr_list[i])) {
      eseq_indexes.push_back(i);
    }
  }

  std::shared_ptr<IRT::Expression> tmp;
  if (!eseq_indexes.empty()) {
    std::shared_ptr<IRT::Statement> stmt;
    std::shared_ptr<IRT::Expression> expr;

    if (eseq_indexes.size() == 1 && eseq_indexes[0] == 0) {
      auto eseq = std::dynamic_pointer_cast<IRT::EseqExpression>(expr_list[0]);
      stmt = eseq->stmt;
      expr_list[0] = eseq->expr;

    } else {
      // make new stmt sequence
      std::vector<std::shared_ptr<IRT::Statement>> stmt_list;
      std::vector<std::shared_ptr<IRT::TempExpression>> temp_list;

      size_t current_eseq_idx = 0;
      for (size_t i = 0; i < expr_list.size(); ++i) {
        std::shared_ptr<IRT::Statement> new_stmt;
        if (current_eseq_idx <= expr_list.size() &&
            i == eseq_indexes[current_eseq_idx]) {
          new_stmt = std::dynamic_pointer_cast<IRT::EseqExpression>(
              expr_list[i])->stmt;
          ++current_eseq_idx;
        } else {
          auto new_temp = std::make_shared<IRT::TempExpression>(IRT::Temporary());
          new_stmt = std::make_shared<IRT::MoveStatement>(
              new_temp,
              expr_list[i]);

          temp_list.push_back(new_temp);
        }

        stmt_list.push_back(new_stmt);
      }

      // make final stmt
      stmt = stmt_list.back();
      for (auto it = ++stmt_list.rbegin(); it != stmt_list.rend(); ++it) {
        stmt = std::make_shared<IRT::SeqStatement>(
            *it,
            stmt);
      }
        
      // update expressions in expression list
      std::shared_ptr<IRT::Expression> new_expr;
      current_eseq_idx = 0;
      size_t current_non_eseq_idx = 0;
      for (size_t i = 0; i < expr_list.size(); ++i) {
        if (current_eseq_idx <= expr_list.size() &&
            i == eseq_indexes[current_eseq_idx]) {
          new_expr = std::dynamic_pointer_cast<IRT::EseqExpression>(
              expr_list[i])->expr;
          ++current_eseq_idx;
        } else {
          new_expr = temp_list[current_non_eseq_idx++];
        }

        expr_list[i] = new_expr;
      }

    }

    tmp = std::make_shared<IRT::EseqExpression>(
        stmt,
        element
        );
  } else {
    tmp = element;
  }

  tos_value_.expr = tmp;

  DEBUG_SINGLE("EseqElimination::CallExpression (finish)")
}

void EseqEliminationVisitor::Visit(std::shared_ptr<ExpressionList> element) {
  DEBUG_SINGLE("EseqElimination::ExpressionList")

  for (auto& expr: element->expr_list) {
    auto tmp = Accept(expr).expr;
    expr = tmp;
  }

  DEBUG_SINGLE("EseqElimination::ExpressionList (finish)")
}

void EseqEliminationVisitor::Visit(std::shared_ptr<NameExpression> element) {
  DEBUG_SINGLE("EseqElimination::NameExpression")

  tos_value_.expr = element;
}

void EseqEliminationVisitor::Visit(std::shared_ptr<EseqExpression> element) {
  DEBUG_SINGLE("EseqElimination::EseqExpression")

  auto stmt = Accept(element->stmt).stmt;
  auto expr = Accept(element->expr).expr;
  element->stmt = stmt;
  element->expr = expr;

  if (IsEseq(expr)) {
    Rehang(element);
  }

  tos_value_.expr = element;

  DEBUG_SINGLE("EseqElimination::EseqExpression (finish)")
}

bool EseqEliminationVisitor::IsEseq(std::shared_ptr<BaseElement> element) {
  DEBUG_START
    DEBUG("EseqElimination::IsEseq")
    DEBUG("element type:")
    DEBUG((int) ident_visitor_->Accept(element))
  DEBUG_FINISH

  return ident_visitor_->Accept(element) == NodeType::EseqExpression;
}

void EseqEliminationVisitor::Rehang(std::shared_ptr<EseqExpression> element) {
  DEBUG_SINGLE("EseqElimination::Rehang")

  assert(IsEseq(element->expr));

  auto eseq = std::dynamic_pointer_cast<IRT::EseqExpression>(element->expr);
  auto new_stmt = std::make_shared<IRT::SeqStatement>(
      element->stmt,
      eseq->stmt);
  element->stmt = new_stmt;
  element->expr = eseq->expr;
}

IRT::IrtStorage EseqEliminationVisitor::Accept(
    std::shared_ptr<BaseElement> element) {
  element->Accept(shared_from_this());
  return tos_value_;
}

}


