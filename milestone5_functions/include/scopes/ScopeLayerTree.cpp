#include "scopes/ScopeLayerTree.hpp"

#include <cassert>


ScopeLayerTree::ScopeLayerTree() {
  root_ = std::make_shared<ScopeLayer>();
  root_->AttachParent(root_);
  root_->AttachClass(root_);
}

void ScopeLayerTree::AddLayer(
    std::shared_ptr<ScopeLayer> parent) const {
  parent->AddChild(std::make_shared<ScopeLayer>(parent));
}

void ScopeLayerTree::AddLayer(
    std::shared_ptr<ScopeLayer> class_scope,
    FunctionType function_type) const {
  class_scope->AddChild(
      std::make_shared<ScopeLayer>(class_scope, function_type));
}

void ScopeLayerTree::SetFunctionScope(
    std::string class_name,
    std::string func_name,
    std::shared_ptr<ScopeLayer> func_scope) {
  function_scopes_[class_name][func_name] = func_scope;
}

std::shared_ptr<ScopeLayer> ScopeLayerTree::GetFunctionScope(
    std::string class_name, std::string func_name) const {
  assert(function_scopes_.find(class_name) != function_scopes_.end());
  assert(function_scopes_.at(class_name).find(func_name) !=
         function_scopes_.at(class_name).end());

  return function_scopes_.at(class_name).at(func_name);
}



std::shared_ptr<ScopeLayer> ScopeLayerTree::GetRoot() const {
  return root_;
}

///////////////////////////////////////////////////////////////////////////////
// ITERATOR
///////////////////////////////////////////////////////////////////////////////

ScopeLayerTree::Iterator::Iterator(
    std::shared_ptr<ScopeLayer> root,
    std::shared_ptr<ScopeLayer> parent, 
    size_t child_index)
  : root_{root}, current_parent_{parent}, current_child_index_{child_index} {
}

ScopeLayerTree::Iterator::Iterator(std::shared_ptr<ScopeLayer> root)
  : Iterator(root, root, 0) {
} 

ScopeLayerTree::Iterator& ScopeLayerTree::Iterator::operator++() {
  if (current_parent_ == root_ &&
      current_child_index_ == root_->GetNumChildren()) {
    throw std::runtime_error("++ ScopeLayerTree::Iterator::end()");
  }

  auto current_layer = current_parent_->GetChild(current_child_index_);
  if (!(current_parent_ == root_ && current_child_index_ == 0) &&
      current_layer->GetNumChildren() > 0) {
    SaveState();
    current_parent_ = current_layer;
    current_child_index_ = 0;
  } else {
    ++current_child_index_;
    while (current_child_index_ == current_parent_->GetNumChildren() &&
        current_parent_ != root_) {
      current_parent_ = current_parent_->GetParent();
      current_child_index_ = last_visited_child_[current_parent_] + 1;
  }
/*
  Note:      
  if (current_parent_ == root_ && 
      current_child_index_ == root_->GetNumChildren()) {
    end() is reached;
  }
*/
  }

  return *this;
}

ScopeLayerTree::Iterator ScopeLayerTree::Iterator::operator++(int) {
  Iterator tmp = *this;
  ++*this;
  return tmp;
}

ScopeLayerTree::Iterator::reference
    ScopeLayerTree::Iterator::operator*() const {
  return current_parent_->GetChild(current_child_index_);
}

std::shared_ptr<ScopeLayer> 
    ScopeLayerTree::Iterator::operator->() const {
  return **this;
}

bool ScopeLayerTree::Iterator::operator==(Iterator other) const {
  return current_parent_ == other.current_parent_ &&
    current_child_index_ == other.current_child_index_;
}

bool ScopeLayerTree::Iterator::operator!=(Iterator other) const {
  return !(*this == other);
}

ScopeLayerTree::Iterator& ScopeLayerTree::Iterator::GoDown() {
  SaveState();
  current_parent_ = current_parent_->GetChild(current_child_index_);
  current_child_index_ = GetLastChildIndex(current_parent_);

  DEBUG_SINGLE("GoDown")
  DEBUG_START 
    DEBUG("Current state:")
    DEBUG("parent:") DEBUG(current_parent_)
    DEBUG("; child index:") DEBUG(current_child_index_)
  DEBUG_FINISH

  return *this;
}

ScopeLayerTree::Iterator& ScopeLayerTree::Iterator::GoUp() {
  SaveState();
  current_parent_ = current_parent_->GetParent();
  current_child_index_ = last_visited_child_[current_parent_];

  DEBUG_SINGLE("GoUp")
  DEBUG_START 
    DEBUG("Current state:")
    DEBUG("parent:") DEBUG(current_parent_)
    DEBUG("; child index:") DEBUG(current_child_index_)
  DEBUG_FINISH

  return *this;
}

void ScopeLayerTree::Iterator::SaveState() {
  last_visited_child_[current_parent_] = current_child_index_;
}

size_t ScopeLayerTree::Iterator::GetLastChildIndex(
    std::shared_ptr<ScopeLayer> parent) {
  if (last_visited_child_.find(parent) == last_visited_child_.end()) {
    last_visited_child_[parent] = 0;
  } else {
    ++last_visited_child_[parent];
  }

  return last_visited_child_[parent];
}

///////////////////////////////////////////////////////////////////////////////

ScopeLayerTree::Iterator ScopeLayerTree::begin() {
  return Iterator(root_);
}

ScopeLayerTree::Iterator ScopeLayerTree::end() {
  return Iterator(root_, root_, root_->GetNumChildren());
}
