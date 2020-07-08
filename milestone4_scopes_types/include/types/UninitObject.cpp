#include "types/UninitObject.hpp"

#include <stdexcept>

int UninitObject::ToInt() const {
    throw std::runtime_error("Variable not initialized");
}

bool UninitObject::ToBool() const {
    throw std::runtime_error("Variable not initialized");
}

