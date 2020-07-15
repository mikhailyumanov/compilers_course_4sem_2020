#pragma once

#include "scopes/Symbol.hpp"
#include "types/Object.hpp"

#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


class ScopeLayer: public std::enable_shared_from_this<ScopeLayer> {
 public:
  explicit ScopeLayer(std::shared_ptr<ScopeLayer> parent);
  ScopeLayer();
  
  void DeclareVariable(Symbol symbol, Type type);
  std::shared_ptr<Object>& Get(Symbol symbol);
  void Set(Symbol symbol, std::shared_ptr<Object> value);

  bool IsDeclared(Symbol symbol) const;
  bool IsDeclaredAnywhere(Symbol symbol) const;

  void AddChild(std::shared_ptr<ScopeLayer> child);
  void AttachParent(std::shared_ptr<ScopeLayer> parent);

  size_t GetNumChildren() const;
  std::shared_ptr<ScopeLayer>& GetChild(size_t index);
  std::shared_ptr<ScopeLayer>& GetParent();

  std::unordered_map<Symbol, std::shared_ptr<Object>> GetVars() const {
    return local_vars_;
  }

 private:
  std::string name_;
  std::shared_ptr<ScopeLayer> parent_;
  std::vector<std::shared_ptr<ScopeLayer>> children_;
  std::unordered_map<Symbol, std::shared_ptr<Object>> local_vars_;
};

