#include "functions/FunctionTable.hpp"

#include <exception>


void FunctionTable::DeclareVariable(Symbol symbol) {
  if (!IsDeclared(symbol)) {
    symbol_offsets_[symbol] = std::stack<size_t>();
  }

  symbol_offsets_[symbol].push(0);
}

size_t FunctionTable::GetOffset(Symbol symbol) const {
  if (!IsDeclared(symbol)) {
    throw std::runtime_error("FunctionTable::GetOffset: " + 
        symbol.GetName() + " is not declared.");
  }

  return symbol_offsets_.at(symbol).top();
}

void FunctionTable::SetOffset(Symbol symbol, size_t offset) {
  if (!IsDeclared(symbol)) {
    throw std::runtime_error("FunctionTable::SetOffset: " + 
        symbol.GetName() + " is not declared.");
  }

  symbol_offsets_[symbol].top() = offset;
}

void FunctionTable::BeginScope() {
  symbols_.push(Symbol("{"));
}

void FunctionTable::EndScope() {
  while (symbols_.top() != Symbol("{")) {
    Symbol symbol = symbols_.top();
    symbol_offsets_[symbol].pop();
    if (symbol_offsets_.empty()) {
      symbol_offsets_.erase(symbol);
    }

    symbols_.pop();
  }

  symbols_.pop();
}

bool FunctionTable::IsDeclared(Symbol symbol) const {
  return symbol_offsets_.find(symbol) != symbol_offsets_.end();
}
