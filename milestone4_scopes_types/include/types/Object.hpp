#pragma once

#include <memory>
#include <string>


class Object: std::enable_shared_from_this<Object> {
 public:
  Object() = default;
  Object(const std::string& type);

  virtual int ToInt() const;
  virtual bool ToBool() const;

  bool IsArray() const;
  void SetArray(bool is_array);

  virtual ~Object() = default;

 protected:
  std::string type_;
  bool is_array_ = false;
};

