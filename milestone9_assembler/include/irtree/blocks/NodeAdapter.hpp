#pragma once

#include "irtree/elements.hpp"


namespace IRT {

class NodeAdapter: public std::enable_shared_from_this<NodeAdapter> {
 public:
  explicit NodeAdapter(std::shared_ptr<SeqStatement> element);

  std::shared_ptr<Statement> GetStmt() const;
  NodeAdapter GetNext() const;
  std::shared_ptr<SeqStatement> GetSeq() const;
  std::shared_ptr<SeqStatement> GetNextSeq() const;
  NodeType GetType() const;

  std::shared_ptr<SeqStatement> GetSeqStmt() const;
  std::shared_ptr<LabelStatement> GetLabelStmt() const;
  std::shared_ptr<JumpStatement> GetJumpStmt() const;
  std::shared_ptr<JumpConditionalStatement> GetCJumpStmt() const;

  bool IsLabelStmt() const;
  bool IsJumpStmt() const;
  bool IsCJumpStmt() const;
  bool IsFinal() const;

  std::string GetLabelName() const;
  std::string GetJumpName() const;
  std::string GetCJumpTrueName() const;
  std::string GetCJumpFalseName() const;

 private:
  std::shared_ptr<SeqStatement> seq_;
};

}
