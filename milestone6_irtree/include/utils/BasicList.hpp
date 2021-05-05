#pragma once

#include <memory>
#include <vector>

#include "utils/BasicElement.hpp"
#include "visitors/Visitor.hpp"


class BasicList: public std::enable_shared_from_this<BasicList> {
 public:
  BasicList();

  virtual ~BasicList() = default;

  void AddItem(std::shared_ptr<BasicElement> item);
  void Accept(std::shared_ptr<Visitor> visitor);

  std::shared_ptr<BasicElement>& operator[](size_t idx);
  const std::shared_ptr<BasicElement>& operator[](size_t idx) const;

  size_t GetLength() const;

  std::vector<std::shared_ptr<BasicElement>> items;
};
