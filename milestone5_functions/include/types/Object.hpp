#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "utils/forward_decl.hpp"


class Object: std::enable_shared_from_this<Object> {
 public:
  Object() = default;
  Object(Type type);

  virtual int ToInt() const;
  virtual bool ToBool() const;

  Type GetType() const;
  std::string GetTypeName() const;
  virtual bool IsClass() const;
  bool IsArray() const;
  void SetArray(bool is_array);

  virtual void Print(std::ostream& stream) const;

  virtual ~Object() = default;

 protected:
  Type type_;
};
