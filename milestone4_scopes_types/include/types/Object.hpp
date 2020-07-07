#pragma once


class Object: std::enable_shared_from_this<Object> {
 public:
   virtual int ToInt();
   virtual ~Object() = default;
};
