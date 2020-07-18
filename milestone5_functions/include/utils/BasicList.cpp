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

std::shared_ptr<BasicElement>& BasicList::operator[](size_t idx) {
  return items[idx];
}


const std::shared_ptr<BasicElement>& BasicList::operator[](size_t idx) const {
  return items[idx];
}

size_t BasicList::GetLength() const {
  return items.size();
}
