#pragma once

#include "types/constructor/IntegerBuilder.hpp"
#include "types/constructor/BoolBuilder.hpp"
#include "types/constructor/ClassBuilder.hpp"


class Constructor {
 public:
  static Constructor& GetInstance();

  Constructor() = default;
  Constructor(const Constructor&) = delete;
  Constructor& operator=(const Constructor&) = delete;
 ~Constructor() = default;

  std::shared_ptr<Object> Construct(std::string type) const;
};
