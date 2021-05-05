#include "utils/BasicList.hpp"


BasicList::BasicList() {
}

void BasicList::AddItem(std::shared_ptr<BasicElement> item) {
  items.push_back(item);
}

void BasicList::Accept(std::shared_ptr<Visitor> visitor) {
  for (auto item : items) {
    item->Accept(visitor);
  }
}
