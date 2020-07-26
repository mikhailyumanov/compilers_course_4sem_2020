#pragma once

#include "utils/BasicList.hpp"

class ClassDeclList: public BasicList,
  public std::enable_shared_from_this<ClassDeclList> {};
