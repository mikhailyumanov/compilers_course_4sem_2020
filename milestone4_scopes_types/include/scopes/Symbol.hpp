#pragma once

#include <string>
#include <unordered_map>
#include <memory>


class Symbol: public std::enable_shared_from_this<Symbol> {
 public:
  Symbol(const std::string& name);
  Symbol(const Symbol& other);

  bool operator==(const Symbol& other) const;
  bool operator!=(const Symbol& other) const;

  std::string GetName() const;

 private:
  std::string name_;
};


namespace std {

template<>
struct hash<Symbol> {
  std::size_t operator()(const Symbol& other) const {
    return hash<string>()(other.GetName());
  }
};    

} // namespace std

