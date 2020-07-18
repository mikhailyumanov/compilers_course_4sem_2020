#pragma once

#include <memory>
#include <stack>
#include <unordered_map>

#include "scopes/Symbol.hpp"
#include "types/Object.hpp"


class FunctionTable: public std::enable_shared_from_this<FunctionTable> {
 public:
  FunctionTable() = default;

  std::shared_ptr<Object> GetOffset(Symbol symbol) const;
  void SetOffset(Symbol symbol, size_t offset);

  void DeclareVariable(Symbol symbol);
  void BeginScope();
  void EndScope();

 private:
  std::stack<Symbol> symbols_;
  std::unordered_map<Symbol, std::stack<std::shared_ptr<Object>> 
    current_offsets_;
}
