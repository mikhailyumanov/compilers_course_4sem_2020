#include "irtree/blocks/BlockTree.hpp"

#include <cassert>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <queue>


namespace IRT {

BlockTree::BlockTree(std::shared_ptr<Statement> pre_root) {
  assert(pre_root != nullptr);
  CanonizeIrtree(pre_root);

  std::shared_ptr<SeqStatement> root;
  if (IRT::GetNodeType(pre_root) != NodeType::SeqStatement) {
    root = std::make_shared<SeqStatement>(
        std::make_shared<LabelStatement>(Label()),
        pre_root);
  } else {
    root = std::dynamic_pointer_cast<SeqStatement>(pre_root);
  }

  //check if first stmt is Label
  if (NodeAdapter(root).GetType() != NodeType::LabelStatement) {
    root = std::make_shared<SeqStatement>(
        std::make_shared<LabelStatement>(Label()),
        root);
  }

  //close last block
  NodeAdapter it(root);
  for (; !it.IsFinal(); it = it.GetNext());
  auto tmp = it.GetSeq()->rhs;
  it.GetSeq()->rhs = std::make_shared<SeqStatement>(
      tmp, 
      std::make_shared<SeqStatement>(
        std::make_shared<JumpStatement>(Label("%done")),
        std::make_shared<SeqStatement>(
          std::make_shared<LabelStatement>(Label("%done")),
          std::make_shared<LabelStatement>(Label()))));

  //set jumps
  it = NodeAdapter(root);
  for (; !it.IsFinal(); it = it.GetNext()) {
    if (it.GetNext().IsLabelStmt() && !(it.IsJumpStmt() || it.IsCJumpStmt())) {
      SetJump(it.GetNextSeq(), it.GetNext().GetLabelStmt()->label);
    }
  }

  //irtree -> block tree
// DEBUG root_ = std::make_shared<Block>(root, std::shared_ptr<SeqStatement>());
  BuildBlocks(root);
}

std::vector<std::shared_ptr<Trace>> BlockTree::GetTraces() const {
  std::vector<std::shared_ptr<Trace>> traces;
  std::vector<std::shared_ptr<Block>> new_trace;
  DFS([&traces, &new_trace](std::shared_ptr<Block> it) {
    DEBUG_SINGLE(it->GetLabelName()) 

    bool is_new_trace = true;
    if (!new_trace.empty()) {
      for (auto&& child : new_trace.back()->GetNext()) {
        if (child->GetLabelName() == it->GetLabelName()) {
          is_new_trace = false;
        }
      }
    }

    if (is_new_trace) {
      if (!new_trace.empty()) {
        traces.push_back(std::make_shared<Trace>(new_trace));
      }
      new_trace = std::vector<std::shared_ptr<Block>>{it};
    } else {
      new_trace.push_back(it);
    }
  });

  traces.push_back(std::make_shared<Trace>(new_trace));
  return traces;
}

void BlockTree::PrintTree(const std::string& filename) const {
  DEBUG_SINGLE("BlockTree::PrintTree")

  static auto print_visitor = std::make_shared<PrintVisitor>(filename);
  root_->GetLabelSeq()->Accept(print_visitor);

  std::ofstream stream(filename + "_blocks");
  Routine routine = [&stream](std::shared_ptr<Block> it) {
//    stream << "Current: " << it->GetLabelName() << std::endl;
//    stream << "Prev: " << std::endl << " > ";
//    for (auto&& prev : it->GetPrev()) {
//      stream << prev->GetLabelName() << ", ";
//    }
//    stream << std::endl << "Next: " << std::endl << " > ";
    for (auto&& next : it->GetNext()) {
      stream << it->GetLabelName() << " " << next->GetLabelName() << std::endl;
    }
    stream << std::endl << std::endl;
  };

  BFS(routine);

  DEBUG_SINGLE("BFS finished")

  stream.close();
}

void BlockTree::BFS(Routine routine) const {
  std::unordered_set<std::string> visited;
  std::queue<std::shared_ptr<Block>> nodes;
  nodes.push(root_);
  while (!nodes.empty()) {
    DEBUG_SINGLE("BFS")
    auto it = nodes.front();
    visited.insert(it->GetLabelName());

    routine(it);

    for (auto&& child : it->GetNext()) {
      if (visited.find(child->GetLabelName()) == visited.end()) {
        nodes.push(child);
      }
    }
    nodes.pop();
  }
}

void BlockTree::DFS(Routine routine) const {
  std::unordered_set<std::string> visited;
  std::stack<std::vector<std::shared_ptr<Block>>> nodes;
  nodes.push({root_});
  while (!nodes.empty()) {
    DEBUG_SINGLE("DFS")
    if (nodes.top().empty()) {
      nodes.pop();
      continue;
    }

    auto it = nodes.top()[0];
    nodes.top().erase(nodes.top().begin());
    if (visited.find(it->GetLabelName()) != visited.end()) {
      continue;
    }
    visited.insert(it->GetLabelName());
    nodes.push(it->GetNext());

    routine(it);
  }
}

void BlockTree::CanonizeIrtree(std::shared_ptr<Statement>& root) const {
  root = std::make_shared<DoubleCallEliminationVisitor>()->Accept(root).stmt;
  root = std::make_shared<EseqEliminationVisitor>()->Accept(root).stmt;
  root = std::make_shared<LinearizeVisitor>()->Accept(root).stmt;
}

void BlockTree::BuildBlocks(std::shared_ptr<SeqStatement> root) {
  std::unordered_map<std::string, std::shared_ptr<Block>> block_mapping;

  // make blocks
  NodeAdapter it{root};
  NodeAdapter current_label{root};
  for (; !it.IsFinal(); it = it.GetNext()) {
    if (it.IsLabelStmt()) {
      current_label = it;
    } else if (it.IsJumpStmt() || it.IsCJumpStmt()) {
      block_mapping[current_label.GetLabelName()] = 
        std::make_shared<Block>(current_label.GetSeq(), it.GetSeq());
    }
    DEBUG_SINGLE(it.GetNext().IsFinal())
  }

  // make 'done' block
  block_mapping["%done"] = std::make_shared<Block>(
      it.GetSeq(), // 'it' points to SeqStmt-parent of 'done' label now.
      std::make_shared<SeqStatement>(
        std::make_shared<JumpStatement>(Label()),
        std::make_shared<LabelStatement>(Label())));

  // set root_
  root_ = block_mapping[NodeAdapter(root).GetLabelName()];

  // bind blocks together
  for (auto&& pair : block_mapping) {
    if (pair.first == "%done") {
      continue;
    }

    DEBUG_SINGLE("build blocks: " + pair.first)
    DEBUG_SINGLE("build blocks: " << (bool) pair.second)

    auto parent = pair.second;
    NodeAdapter jump{parent->GetJumpSeq()};
    if (jump.IsJumpStmt()) {
      auto child = block_mapping[jump.GetJumpName()];
      parent->AddNext(child);
      child->AddPrev(parent);

    } else if (jump.IsCJumpStmt()) {
      auto true_child = block_mapping[jump.GetCJumpTrueName()];
      auto false_child = block_mapping[jump.GetCJumpFalseName()];
      parent->AddNext(false_child); // false lable first
      parent->AddNext(true_child);
      true_child->AddPrev(parent);
      false_child->AddPrev(parent);
    }
  }
}

void BlockTree::SetJump(std::shared_ptr<SeqStatement> element, Label label) {
  auto tmp = element->lhs;
  element->lhs = std::make_shared<JumpStatement>(label);
  element->rhs = std::make_shared<SeqStatement>(tmp, element->rhs);
}

}
