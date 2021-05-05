#include "irtree/blocks/NodeAdapter.hpp"

#include <cassert>


namespace IRT {

NodeAdapter::NodeAdapter(std::shared_ptr<SeqStatement> element)
  : seq_{element} {
}

std::shared_ptr<Statement> NodeAdapter::GetStmt() const {
  return seq_->lhs;
}

NodeAdapter NodeAdapter::GetNext() const {
  assert(GetNodeType(seq_->rhs) == NodeType::SeqStatement);
  return NodeAdapter(std::dynamic_pointer_cast<SeqStatement>(seq_->rhs));
}

std::shared_ptr<SeqStatement> NodeAdapter::GetSeq() const {
  return std::dynamic_pointer_cast<SeqStatement>(seq_);
}

std::shared_ptr<SeqStatement> NodeAdapter::GetNextSeq() const {
  return GetNext().GetSeq();
}

NodeType NodeAdapter::GetType() const {
  return IRT::GetNodeType(GetStmt());
}

std::shared_ptr<LabelStatement> NodeAdapter::GetLabelStmt() const {
  assert(GetType() == NodeType::LabelStatement);
  return std::dynamic_pointer_cast<LabelStatement>(GetStmt());
}

std::shared_ptr<JumpStatement> NodeAdapter::GetJumpStmt() const {
  assert(GetType() == NodeType::JumpStatement);
  return std::dynamic_pointer_cast<JumpStatement>(GetStmt());
}

std::shared_ptr<JumpConditionalStatement> NodeAdapter::GetCJumpStmt() const {
  assert(GetType() == NodeType::JumpConditionalStatement);
  return std::dynamic_pointer_cast<JumpConditionalStatement>(GetStmt());
}

bool NodeAdapter::IsLabelStmt() const {
  return GetType() == NodeType::LabelStatement;
}

bool NodeAdapter::IsJumpStmt() const {
  return GetType() == NodeType::JumpStatement;
}

bool NodeAdapter::IsCJumpStmt() const {
  return GetType() == NodeType::JumpConditionalStatement;
}

bool NodeAdapter::IsFinal() const {
  return GetNodeType(seq_->rhs) != NodeType::SeqStatement;
}

std::string NodeAdapter::GetLabelName() const {
  return GetLabelStmt()->label.ToString();
}

std::string NodeAdapter::GetJumpName() const {
  return GetJumpStmt()->label.ToString();
}

std::string NodeAdapter::GetCJumpTrueName() const {
  return GetCJumpStmt()->label_true.ToString();
}

std::string NodeAdapter::GetCJumpFalseName() const {
  return GetCJumpStmt()->label_false.ToString();
}

}
