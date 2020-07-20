#include "utils/BasicElement.hpp"


void BasicElement::SetLocation(yy::location new_loc) {
  location = new_loc;
}

yy::location BasicElement::GetLocation() const {
  return location;
}
