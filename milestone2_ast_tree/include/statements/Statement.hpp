#pragma once

#include <memory>


class Statement: std::enable_shared_from_this<Statement> {
 public:
  virtual void Perform() const = 0;
};
