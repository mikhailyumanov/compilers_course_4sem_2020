#include "utils/BasicList.hpp"


template <class T>
BasicList<T>::BasicList() {
}

template <class T>
BasicList<T>::AddItem(std::shared_ptr<T> item) {
  items_.push_back(item);
}
