#include "types/UninitObject.hpp"

#include <stdexcept>


UninitObject::UninitObject(Type type) : Object(type) {
}

int UninitObject::ToInt() const {
    throw std::runtime_error("Variable not initialized");
}

bool UninitObject::ToBool() const {
    throw std::runtime_error("Variable not initialized");
}

