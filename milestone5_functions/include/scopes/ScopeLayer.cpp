#include "scopes/ScopeLayer.hpp"
#include "types/UninitObject.hpp"

#include <iostream>


ScopeLayer::ScopeLayer(std::shared_ptr<ScopeLayer> parent)
  : parent_(parent) {
}


ScopeLayer::ScopeLayer() {
}


void ScopeLayer::DeclareVariable(Symbol symbol, Type type) {
  if (IsDeclared(symbol)) {
    throw std::runtime_error("Variable has locally declared");
  }

  local_vars_[symbol] = std::make_shared<UninitObject>(type);
}


std::shared_ptr<Object>& ScopeLayer::Get(Symbol symbol) {
  auto current_scope = shared_from_this();

  while (!current_scope->IsDeclared(symbol) &&
      current_scope->parent_ != current_scope) {
    current_scope = current_scope->parent_;
  }

  if (current_scope->IsDeclared(symbol)) {
    return current_scope->local_vars_[symbol];
  } else {
    throw std::runtime_error("Variable not declared");
  }
}


void ScopeLayer::Set(Symbol symbol, std::shared_ptr<Object> value) {
  Get(symbol) = value;
}

bool ScopeLayer::IsDeclared(Symbol symbol) const {
  return local_vars_.find(symbol) != local_vars_.end();
}


bool ScopeLayer::IsDeclaredAnywhere(Symbol symbol) const {
  return IsDeclared(symbol) || 
    (parent_ != shared_from_this() && parent_->IsDeclaredAnywhere(symbol));
}


void ScopeLayer::AddChild(std::shared_ptr<ScopeLayer> child) {
  children_.push_back(child);
  child->parent_ = shared_from_this();
}


void ScopeLayer::AttachParent(std::shared_ptr<ScopeLayer> parent) {
  parent->AddChild(shared_from_this());
}


size_t ScopeLayer::GetNumChildren() const {
  return children_.size();
}


std::shared_ptr<ScopeLayer>& ScopeLayer::GetChild(size_t index) {
  DEBUG_SINGLE("ScopeLayer::GetChild")
  auto ret_val = children_[index];
  DEBUG_SINGLE("This is fine")
  return children_[index];
}


std::shared_ptr<ScopeLayer>& ScopeLayer::GetParent() {
  return parent_;
}

