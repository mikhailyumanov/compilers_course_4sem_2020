#pragma once

#include "scopes/ScopeLayer.hpp"

class ScopeLayerTree: public std::enable_shared_from_this<ScopeLayerTree> {
 public:
  explicit ScopeLayerTree(std::shared_ptr<ScopeLayer> root);

 public:
  std::shared_ptr<ScopeLayer> root_;
};
