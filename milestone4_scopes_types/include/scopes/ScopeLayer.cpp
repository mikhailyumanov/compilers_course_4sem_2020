#include "scopes/ScopeLayer.hpp"
#include "types/UninitObject.hpp"

#include <iostream>


ScopeLayer::ScopeLayer(std::shared_ptr<ScopeLayer> parent)
  : parent_(parent) {
    std::cout << "Constructor called" << std::endl;
    std::cout << "End contstructor called" << std::endl;

    parent_->AddChild(shared_from_this());
}


void ScopeLayer::AttachParent() {
  //TODO
}


ScopeLayer::ScopeLayer(): parent_{shared_from_this()} {
}


void ScopeLayer::DeclareVariable(Symbol symbol) {
  if (IsDeclared(symbol)) {
    throw std::runtime_error("Variable has locally declared");
  }

  local_vars_[symbol] = std::make_shared<UninitObject>();
}


std::pair<Symbol, std::shared_ptr<Object>>& ScopeLayer::GetSymbol(
    Symbol symbol) {
  auto current_layer = shared_from_this();

  while (!current_layer->IsDeclared(symbol) &&
      current_layer->parent_ != current_layer) {
    current_layer = current_layer->parent_;
  }

  if (current_layer->IsDeclared(symbol)) {
    return current_layer->local_vars_.find(symbol);
  } else {
    throw std::runtime_error("Variable not declared");
  }
}


std::shared_ptr<Object> ScopeLayer::GetValue(Symbol symbol) {
  return GetSymbol(symbol).second;
}


void ScopeLayer::SetValue(Symbol symbol, std::shared_ptr<Object> value) {
  GetSymbol(symbol).second = value;
}


bool ScopeLayer::IsDeclared(Symbol symbol) {
  return local_vars_.find(symbol) != local_vars_.end();
}


void ScopeLayer::AddChild(std::shared_ptr<ScopeLayer> child) {
  children_.push_back(child);
}


std::shared_ptr<ScopeLayer> ScopeLayer::GetChild(size_t index) {
  std::cout << "Children of scope: " << children_.size() << std::endl;
  return children_[index];
}


std::shared_ptr<ScopeLayer> ScopeLayer::GetParent() const {
  return parent_;
}

