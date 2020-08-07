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
  BlockTree() = default;
  explicit BlockTree(std::shared_ptr<Statement> root, bool is_main = false);

  std::vector<std::shared_ptr<Trace>> GetTraces() const;
  void PrintTree(const std::string& filename) const;
  void PrintJouette(const std::string& filename) const;

  std::shared_ptr<Jouette::PrintVisitor> GetPrinter(const std::string&) const;

 private:
  void DFS(Routine f) const;
  void BFS(Routine f) const;
  void CanonizeIrtree(std::shared_ptr<Statement>& root) const;
  void BuildBlocks(std::shared_ptr<SeqStatement> root);

  void SetJump(std::shared_ptr<SeqStatement> element, Label label);

 private:
  std::shared_ptr<Block> root_;
  bool is_main_ = false;
};

}
