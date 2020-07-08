#pragma once

#include "scopes/Symbol.hpp"
#include "types/Object.hpp"

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>


class ScopeLayer: public std::enable_shared_from_this<ScopeLayer> {
 public:
    explicit ScopeLayer(std::shared_ptr<ScopeLayer> parent);
    ScopeLayer();
  
    void DeclareVariable(Symbol symbol);
    std::shared_ptr<Object>& GetSymbol(Symbol symbol);
    std::shared_ptr<Object> GetValue(Symbol symbol);
    void SetValue(Symbol symbol, std::shared_ptr<Object> value);

    bool IsDeclared(Symbol symbol) const;

    void AddChild(std::shared_ptr<ScopeLayer> child);
    void AttachParent();

    std::shared_ptr<ScopeLayer> GetChild(size_t index);
    std::shared_ptr<ScopeLayer> GetParent() const;

 private:
    std::string name_;
    std::shared_ptr<ScopeLayer> parent_;
    std::vector<std::shared_ptr<ScopeLayer>> children_;
    std::unordered_map<Symbol, std::shared_ptr<Object>> local_vars_;
};
