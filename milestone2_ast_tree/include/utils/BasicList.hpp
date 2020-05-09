#pragma once

#include <memory>
#include <vector>


template <class T>
class BasicList : enable_shared_from_this<BasicList> {
 public:
  BasicList();

  AddItem(std::shared_ptr<T> item);

 private:
  std::vector<std::shared_ptr<T>> items_;
}
