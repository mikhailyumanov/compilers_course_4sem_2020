#pragma once

#include <functional>

#include "irtree/blocks/NodeAdapter.hpp"
#include "irtree/blocks/Block.hpp"
#include "irtree/blocks/Trace.hpp"
#include "irtree/visitors/IdentVisitor.hpp"

namespace IRT {

using Routine = std::function<void(std::shared_ptr<Block>)>;

class BlockTree: public std::enable_shared_from_this<BlockTree> {
 public:
  explicit BlockTree(std::shared_ptr<Statement> root);

  std::vector<std::shared_ptr<Trace>> GetTraces() const;
  void PrintTree(const std::string& filename) const;

 private:
  void DFS(Routine f) const;
  void BFS(Routine f) const;
  void CanonizeIrtree(std::shared_ptr<Statement>& root) const;
  void BuildBlocks(std::shared_ptr<SeqStatement> root);

  void SetJump(std::shared_ptr<SeqStatement> element, Label label);

 private:
  std::shared_ptr<Block> root_;
};

}
