#pragma once

#include "irtree/blocks/Block.hpp"
#include "irtree/visitors/IdentVisitor.hpp"


namespace IRT {

class BlockTree: public std::enable_shared_from_this<BlockTree> {
 public:
  explicit BlockTree(std::shared_ptr<Statement> root);

  void PrintTree(const std::string& filename) const;

 private:
  void CanonizeIrtree(std::shared_ptr<SeqStatement> root) const;
  void BuildBlocks(std::shared_ptr<SeqStatement> root);

  std::shared_ptr<Statement> GetStmt(
      std::shared_ptr<SeqStatement> element) const;
  std::shared_ptr<SeqStatement> GetNextSeq(
      std::shared_ptr<SeqStatement> element) const;
  NodeType GetType(std::shared_ptr<Statement> stmt);
  void SetJump(std::shared_ptr<SeqStatement> element,
      Label label);

 private:
  std::shared_ptr<Block> root_;
  std::shared_ptr<IdentVisitor> ident_visitor_;
};

}
