#pragma once

#include <memory>
#include <stack>
#include <unordered_map>

#include "scopes/Symbol.hpp"


class FunctionTable: public std::enable_shared_from_this<FunctionTable> {
 public:
  FunctionTable() = default;

  void DeclareVariable(Symbol symbol);

  size_t GetOffset(Symbol symbol) const;
  void SetOffset(Symbol symbol, size_t offset);

  bool IsDeclared(Symbol symbol) const;

  void BeginScope();
  void EndScope();

#if !DEBUG_ON
 private:
#endif
 
  std::stack<Symbol> symbols_;
  std::unordered_map<Symbol, std::stack<size_t>> symbol_offsets_;
};
