#pragma once

#include "scopes/ScopeLayer.hpp"

class ScopeLayerTree: public std::enable_shared_from_this<ScopeLayerTree> {
 public:
  ScopeLayerTree();

  void AddLayer(std::shared_ptr<ScopeLayer> parent) const;
  void AddLayer(std::shared_ptr<ScopeLayer> class_scope,
      FunctionType function_type) const;

  void SetFunctionScope(std::string class_name, std::string func_name,
      std::shared_ptr<ScopeLayer> func_scope);
  std::shared_ptr<ScopeLayer> GetFunctionScope(
      std::string class_name, std::string func_name) const;

  std::shared_ptr<ScopeLayer> GetRoot() const;
  

 private:
  std::shared_ptr<ScopeLayer> root_;
  std::unordered_map<std::string,
    std::unordered_map<std::string,
      std::shared_ptr<ScopeLayer>>> function_scopes_;

  // iterator
 public:
  class Iterator;

  Iterator begin();
  Iterator end();
};

class ScopeLayerTree::Iterator: public std::iterator<
      std::input_iterator_tag,            // iterator_category
      std::shared_ptr<ScopeLayer>,        // value_type
      long,                               // difference_type
      const std::shared_ptr<ScopeLayer>*, // pointer
      std::shared_ptr<ScopeLayer>&        // reference
  > {
 public:
  Iterator() = default;
  explicit Iterator(std::shared_ptr<ScopeLayer> root,
      std::shared_ptr<ScopeLayer> parent, size_t child_index);
  explicit Iterator(std::shared_ptr<ScopeLayer> root); 

  Iterator& operator++();
  Iterator  operator++(int);
  reference operator*() const;
  std::shared_ptr<ScopeLayer> operator->() const;
  bool operator==(Iterator other) const;
  bool operator!=(Iterator other) const;  

  Iterator& GoDown();
  Iterator& GoUp();

// private:
  void SaveState();
  size_t GetLastChildIndex(std::shared_ptr<ScopeLayer> parent);

// private:
  std::shared_ptr<ScopeLayer> root_;
  std::shared_ptr<ScopeLayer> current_parent_;
  size_t current_child_index_;
  std::unordered_map<std::shared_ptr<ScopeLayer>, size_t> last_visited_child_;
};
