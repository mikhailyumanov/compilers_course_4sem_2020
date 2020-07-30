#pragma once

#include <functional>

#include "irtree/blocks/Block.hpp"
//#include "irtree/blocks/Trace.hpp"
#include "irtree/visitors/IdentVisitor.hpp"

namespace IRT {

using Routine = std::function<void(std::shared_ptr<Block>)>;

class BlockTree: public std::enable_shared_from_this<BlockTree> {
 public:
  explicit BlockTree(std::shared_ptr<Statement> root);

  void PrintTree(const std::string& filename) const;

 private:
  void BFS(Routine f) const;
  void CanonizeIrtree(std::shared_ptr<Statement>& root) const;
  void BuildBlocks(std::shared_ptr<SeqStatement> root);

  std::shared_ptr<Statement> GetStmt(
      std::shared_ptr<SeqStatement> element) const;
  std::shared_ptr<SeqStatement> GetNextSeq(
      std::shared_ptr<SeqStatement> element) const;
  NodeType GetType(std::shared_ptr<Statement> stmt) const;
  void SetJump(std::shared_ptr<SeqStatement> element,
      Label label);

 private:
  std::shared_ptr<SeqStatement> 
    GetSeqStmt(std::shared_ptr<Statement>) const;
  std::shared_ptr<LabelStatement> 
    GetLabelStmt(std::shared_ptr<Statement>) const;
  std::shared_ptr<JumpStatement> 
    GetJumpStmt(std::shared_ptr<Statement>) const;
  std::shared_ptr<JumpConditionalStatement> 
    GetCJumpStmt(std::shared_ptr<Statement>) const;

 private:
  std::shared_ptr<Block> root_;
};

}
