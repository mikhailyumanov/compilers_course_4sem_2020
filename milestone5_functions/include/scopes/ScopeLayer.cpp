#include "scopes/ScopeLayer.hpp"
#include "types/UninitObject.hpp"

#include <iostream>


ScopeLayer::ScopeLayer(std::shared_ptr<ScopeLayer> parent)
  : parent_{parent}, class_scope_{parent->class_scope_},
    function_type_{parent->function_type_} {
}

ScopeLayer::ScopeLayer(std::shared_ptr<ScopeLayer> parent,
    FunctionType function_type)
  : parent_{parent}, class_scope_{parent}, function_type_{function_type} {
}


void ScopeLayer::DeclareVariable(Symbol symbol, Type type) {
  /*
  DEBUG_START
    DEBUG("ScopeLayer::DeclareVariable")
    DEBUG(symbol.GetName())
    DEBUG(type)
  DEBUG_FINISH
  */

  if (IsDeclared(symbol)) {
    throw std::runtime_error("Variable has locally declared");
  }

//  DEBUG_SINGLE("ScopeLayer::DeclareVariable init")
  local_vars_[symbol] = std::make_shared<UninitObject>(type);
}


std::shared_ptr<Object>& ScopeLayer::Get(Symbol symbol) {
  // XXX: remember: there are actually two functions
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

const std::shared_ptr<Object>& ScopeLayer::Get(Symbol symbol) const {
  // XXX: remember: there are actually two functions
  auto current_scope = shared_from_this();

  while (!current_scope->IsDeclared(symbol) &&
      current_scope->parent_ != current_scope) {
    current_scope = current_scope->parent_;
  }

  if (current_scope->IsDeclared(symbol)) {
    return current_scope->local_vars_.at(symbol);
  } else {
    throw std::runtime_error("Variable not declared");
  }
}

void ScopeLayer::Set(Symbol symbol, std::shared_ptr<Object> value) {
  Get(symbol) = value;
}

bool ScopeLayer::IsClassData(Symbol symbol) const {
//  DEBUG_SINGLE("ScopeLayer::IsClassData")
  if (function_type_.IsMain() || class_scope_ == shared_from_this()) {
    return false;
  } 

  return class_scope_->IsDeclared(symbol);
}

bool ScopeLayer::IsArgument(Symbol symbol) const {
//  DEBUG_SINGLE("ScopeLayer::IsArgument")
  if (function_type_.IsMain()) {
    return false;
  } 

  for (auto&& name : function_type_.arg_names) {
    if (name == symbol.GetName()) {
      return true;
    }
  }

  return false;
}

Type ScopeLayer::GetType(Symbol symbol) const {
//  DEBUG_SINGLE("ScopeLayer::GetType")
  if (local_vars_.find(symbol) != local_vars_.end()) {
    return Get(symbol)->GetType();
  } else if (IsArgument(symbol)) {
    for (size_t i = 0; i < function_type_.GetNumArgs(); ++i) {
      if (function_type_.arg_names[i] == symbol.GetName()) {
        return function_type_.arg_types[i];
      }
    }
  } else if (IsClassData(symbol)) {
    return class_scope_->GetType(symbol);
  } else {
    return parent_->GetType(symbol);
  }
}

void ScopeLayer::SetMain() {
//  DEBUG_SINGLE("ScopeLayer::SetMain")
  function_type_.is_main = true;
}

bool ScopeLayer::IsDeclared(Symbol symbol) const {
//  DEBUG_SINGLE("ScopeLayer::IsDeclared")
  return local_vars_.find(symbol) != local_vars_.end() || IsArgument(symbol) ||
    IsClassData(symbol);
}


bool ScopeLayer::IsDeclaredAnywhere(Symbol symbol) const {
//  DEBUG_SINGLE("ScopeLayer::IsDeclaredAnywhere")
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


void ScopeLayer::AttachClass(std::shared_ptr<ScopeLayer> class_scope) {
  class_scope_ = class_scope;
}


size_t ScopeLayer::GetNumChildren() const {
  return children_.size();
}


std::shared_ptr<ScopeLayer>& ScopeLayer::GetChild(size_t index) {
  return children_[index];
}


std::shared_ptr<ScopeLayer>& ScopeLayer::GetParent() {
  return parent_;
}

