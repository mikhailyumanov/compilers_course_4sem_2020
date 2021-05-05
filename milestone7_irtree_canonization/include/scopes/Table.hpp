#pragma once

#include "scopes/Symbol.hpp"
#include "types/Object.hpp"

#include <unordered_map>
#include <stack>


class Table: public std::enable_shared_from_this<Table> {
 public:
  void Put(Symbol symbol, std::shared_ptr<Object> value);
  void CreateVariable(Symbol symbol);
  Symbol GetSymbol(const std::string& name);
  std::shared_ptr<Object> Get(Symbol key);
    
  void BeginScope();
  void EndScope();

 private:
  std::unordered_map<Symbol, std::stack<std::shared_ptr<Object>>> values_;
  std::unordered_map<std::string, Symbol> symbols_map_;
  std::stack<Symbol> symbols_;

};
