#include "irtree/visitors/JouetteVisitor.hpp"

#include <cassert>


namespace IRT {

JouetteVisitor::JouetteVisitor() {
}

void JouetteVisitor::Visit(std::shared_ptr<ExpStatement> element) {
  tos_value_ = Accept(element->GetExpression());

  DEBUG_SINGLE("JouetteAssembler::ExpStatement")
}

void JouetteVisitor::Visit(std::shared_ptr<JumpConditionalStatement> element) {
  DEBUG_SINGLE("JouetteAssembler::JumpConditionalStatement start")

  auto lhs = Accept(element->lhs);
  auto rhs = Accept(element->rhs);
  auto flag = std::make_shared<Jouette::Register>();

  switch (element->operator_type) {
    case LogicOperatorType::LT :
      lst.push_back(std::make_shared<Jouette::Sub>(flag, lhs, rhs));
      lst.push_back(std::make_shared<Jouette::Blt>(element->label_true, flag));
      break;

    case LogicOperatorType::GT :
      lst.push_back(std::make_shared<Jouette::Sub>(flag, lhs, rhs));
      lst.push_back(std::make_shared<Jouette::Blt>(element->label_false, flag));
      lst.push_back(std::make_shared<Jouette::Bne>(element->label_true, flag));
      break;

    case LogicOperatorType::EQ :
      lst.push_back(std::make_shared<Jouette::Sub>(flag, lhs, rhs));
      lst.push_back(std::make_shared<Jouette::Beq>(element->label_true, flag));
      break;

    case LogicOperatorType::NE : 
      lst.push_back(std::make_shared<Jouette::Sub>(flag, lhs, rhs));
      lst.push_back(std::make_shared<Jouette::Bne>(element->label_true, flag));
      break;

    default : assert(false);

  }

  DEBUG_SINGLE("JouetteAssembler::JumpConditionalStatement")
}

void JouetteVisitor::Visit(std::shared_ptr<MoveStatement> element) {
  DEBUG_SINGLE("JouetteAssembler::MoveStatement start")

  std::shared_ptr<Jouette::Command> cmnd;
  if (Jouette::StoreRightConstRule().IsSuitable(element)) {
    auto binop_expr = GetBinopExpr(GetMemExpr(element->target)->expr);
    auto tmp_a = Accept(binop_expr->lhs);
    auto tmp_d = Accept(element->source);
    int cnst = GetConstExpr(binop_expr->rhs)->GetValue();
    cmnd = std::make_shared<Jouette::Store>(tmp_a, cnst, tmp_d);

  } else if (Jouette::StoreLeftConstRule().IsSuitable(element)) {
    auto binop_expr = GetBinopExpr(GetMemExpr(element->target)->expr);
    auto tmp_a = Accept(binop_expr->rhs);
    auto tmp_d = Accept(element->source);
    int cnst = GetConstExpr(binop_expr->lhs)->GetValue();
    cmnd = std::make_shared<Jouette::Store>(tmp_a, cnst, tmp_d);
  
  } else if (Jouette::StoreConstRule().IsSuitable(element)) {
    auto tmp_d = Accept(element->source);
    auto cnst = GetConstExpr(GetMemExpr(element->target)->expr)->GetValue();
    cmnd = std::make_shared<Jouette::Store>(
        Jouette::GetNullRegister(), cnst, tmp_d);
  
  } else if (Jouette::MovemRule().IsSuitable(element)) {
    auto tmp_target = Accept(element->target);
    auto tmp_source = Accept(element->source);
    cmnd = std::make_shared<Jouette::Movem>(tmp_target, tmp_source);
  
  } else if (Jouette::StoreRule().IsSuitable(element)) {
    auto mem_expr = GetMemExpr(element->target);
    auto tmp_a = Accept(mem_expr->expr);
    auto tmp_d = Accept(element->source);
    cmnd = std::make_shared<Jouette::Store>(tmp_a, 0, tmp_d);
  
  } else if (Jouette::MoveTempRule().IsSuitable(element)) {
    auto tmp_a = Accept(element->target);
    auto tmp_d = Accept(element->source);
    *tos_value_ = *tmp_a;

    DEBUG_SINGLE("JouetteAssembler::MoveStatement")
    return;

  } else {
    assert(false);
  }

  lst.push_back(cmnd);

  DEBUG_SINGLE("JouetteAssembler::MoveStatement")
}

void JouetteVisitor::Visit(std::shared_ptr<SeqStatement> element) {
  element->lhs->Accept(shared_from_this());
  element->rhs->Accept(shared_from_this());

  DEBUG_SINGLE("JouetteAssembler::SeqStatement")
}

void JouetteVisitor::Visit(std::shared_ptr<LabelStatement> element) {
  lst.push_back(std::make_shared<Jouette::Label>(element->label));

  DEBUG_SINGLE("JouetteAssembler::LabelStatement")
}

void JouetteVisitor::Visit(std::shared_ptr<JumpStatement> element) {
  lst.push_back(std::make_shared<Jouette::Jump>(element->label));

  DEBUG_SINGLE("JouetteAssembler::JumpStatement")
}

void JouetteVisitor::Visit(std::shared_ptr<ReturnStatement> element) {
  lst.push_back(std::make_shared<Jouette::Return>());

  DEBUG_SINGLE("JouetteAssembler::ReturnStatement")
}

void JouetteVisitor::Visit(std::shared_ptr<ConstExpression> element) {
  tos_value_ = std::make_shared<Jouette::Register>();
  lst.push_back(std::make_shared<Jouette::Addi>(
        tos_value_, Jouette::GetNullRegister(), element->GetValue()));

  DEBUG_SINGLE("JouetteAssembler::ConstExpression")
}

void JouetteVisitor::Visit(std::shared_ptr<BinopExpression> element) {
  auto output = std::make_shared<Jouette::Register>();
  std::shared_ptr<Jouette::Expression> expr;
  if (Jouette::AddiLeftConstRule().IsSuitable(element)) {
    auto tmp = Accept(element->rhs);
    int cnst = GetConstExpr(element->lhs)->GetValue();
    expr = std::make_shared<Jouette::Addi>(output, tmp, cnst);
  
  } else if (Jouette::AddiRightConstRule().IsSuitable(element)) {
    auto tmp = Accept(element->lhs);
    int cnst = GetConstExpr(element->rhs)->GetValue();
    expr = std::make_shared<Jouette::Addi>(output, tmp, cnst);
  
  } else if (Jouette::SubiRule().IsSuitable(element)) {
    auto tmp = Accept(element->lhs);
    int cnst = GetConstExpr(element->rhs)->GetValue();
    expr = std::make_shared<Jouette::Subi>(output, tmp, cnst);
  
  } else {
    auto lhs = Accept(element->lhs);
    auto rhs = Accept(element->rhs);

    if (Jouette::AddRule().IsSuitable(element)) {
      expr = std::make_shared<Jouette::Add>(output, lhs, rhs);

    } else if (Jouette::SubRule().IsSuitable(element)) {
      expr = std::make_shared<Jouette::Sub>(output, lhs, rhs);

    } else if (Jouette::MulRule().IsSuitable(element)) {
      expr = std::make_shared<Jouette::Mul>(output, lhs, rhs);

    } else if (Jouette::DivRule().IsSuitable(element)) {
      expr = std::make_shared<Jouette::Div>(output, lhs, rhs);
    
    } else {
      assert(false);
    }
  }

  tos_value_ = output;
  lst.push_back(expr);

  DEBUG_SINGLE("JouetteAssembler::BinopExpression")
}

void JouetteVisitor::Visit(std::shared_ptr<TempExpression> element) {
  tos_value_ = std::make_shared<Jouette::Register>(element->temp);

  DEBUG_SINGLE("JouetteAssembler::TempExpression")
}

void JouetteVisitor::Visit(std::shared_ptr<MemExpression> element) {
  auto output = std::make_shared<Jouette::Register>();
  std::shared_ptr<Jouette::Load> cmnd;

  if (Jouette::LoadRightConstRule().IsSuitable(element)) {
    auto binop_expr = GetBinopExpr(element->expr);
    auto tmp = Accept(binop_expr->lhs);
    int cnst = GetConstExpr(binop_expr->rhs)->GetValue();
    cmnd = std::make_shared<Jouette::Load>(output, tmp, cnst);

  } else if (Jouette::LoadLeftConstRule().IsSuitable(element)) {
    auto binop_expr = GetBinopExpr(element->expr);
    auto tmp = Accept(binop_expr->rhs);
    int cnst = GetConstExpr(binop_expr->lhs)->GetValue();
    cmnd = std::make_shared<Jouette::Load>(output, tmp, cnst);
  
  } else if (Jouette::LoadConstRule().IsSuitable(element)) {
    auto cnst = GetConstExpr(element->expr)->GetValue();
    cmnd = std::make_shared<Jouette::Load>(
        output, Jouette::GetNullRegister(), cnst);
  
  } else if (Jouette::LoadRule().IsSuitable(element)) {
    auto tmp = Accept(element->expr);
    cmnd = std::make_shared<Jouette::Load>(output, tmp, 0);
  
  } else {
    assert(false);
  }

  tos_value_ = output;
  lst.push_back(cmnd);

  DEBUG_SINGLE("JouetteAssembler::MemExpression")
}

void JouetteVisitor::Visit(std::shared_ptr<CallExpression> element) {
  std::vector<std::shared_ptr<Jouette::Register>> args;
  for (auto&& expr : element->args->expr_list) {
    args.push_back(Accept(expr));
  }

  tos_value_ = std::make_shared<Jouette::Register>();
  lst.push_back(std::make_shared<Jouette::Call>(tos_value_,
      Jouette::Label(GetNameExpr(element->function_name)->label), args));

  DEBUG_SINGLE("JouetteAssembler::CallExpression")
}

void JouetteVisitor::Visit(std::shared_ptr<ExpressionList> element) {
  DEBUG_SINGLE("JouetteAssembler::ExpressionList")
  // do nothing
}

void JouetteVisitor::Visit(std::shared_ptr<NameExpression> element) {
  DEBUG_SINGLE("JouetteAssembler::NameExpression")
  // do nothing
}

void JouetteVisitor::Visit(std::shared_ptr<EseqExpression> element) {
  DEBUG_SINGLE("JouetteAssembler::EseqExpression")
  // do nothing
}

std::shared_ptr<Jouette::Register> JouetteVisitor::Accept(
    std::shared_ptr<BaseElement> element) {
  element->Accept(shared_from_this());
  return tos_value_;
}

const std::vector<std::shared_ptr<Jouette::Instruction>>& 
  JouetteVisitor::GetInstructions() const {
  return lst;
}

}
