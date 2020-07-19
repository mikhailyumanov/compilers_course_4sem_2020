#pragma once

#include "scopes/Symbol.hpp"
#include "types/Object.hpp"
#include "types/FunctionType.hpp"

#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


class ScopeLayer: public std::enable_shared_from_this<ScopeLayer> {
 public:
  explicit ScopeLayer(std::shared_ptr<ScopeLayer> parent);
  ScopeLayer(std::shared_ptr<ScopeLayer> parent,
      FunctionType function_type);
  ScopeLayer() = default;
  
  void DeclareVariable(Symbol symbol, Type type);
  std::shared_ptr<Object>& Get(Symbol symbol);
  const std::shared_ptr<Object>& Get(Symbol symbol) const;
  void Set(Symbol symbol, std::shared_ptr<Object> value);

  bool IsClassData(Symbol symbol) const;
  bool IsArgument(Symbol symbol) const;
  size_t GetArgIndex(Symbol symbol) const;
  Type GetType(Symbol symbol) const;

  bool IsDeclared(Symbol symbol) const;
  bool IsDeclaredAnywhere(Symbol symbol) const;

  void AddChild(std::shared_ptr<ScopeLayer> child);
  void AttachParent(std::shared_ptr<ScopeLayer> parent);
  void AttachClass(std::shared_ptr<ScopeLayer> class_scope);

  size_t GetNumChildren() const;
  std::shared_ptr<ScopeLayer>& GetChild(size_t index);
  std::shared_ptr<ScopeLayer>& GetParent();

  bool IsMain() const;
  void SetMain();
  void UnsetMain();

  FunctionType GetFunctionType() const;

#if DEBUG_ON
  std::unordered_map<Symbol, std::shared_ptr<Object>> GetVars() const {
    return local_vars_;
  }
#endif

 private:
  std::string name_;
  std::shared_ptr<ScopeLayer> parent_;
  std::vector<std::shared_ptr<ScopeLayer>> children_;
  std::unordered_map<Symbol, std::shared_ptr<Object>> local_vars_;

  std::shared_ptr<ScopeLayer> class_scope_;
  FunctionType function_type_;
  bool is_main_ = false;
};

