#pragma once

#include "utils/BasicList.hpp"

class DeclList: public BasicList,
  public std::enable_shared_from_this<DeclList> {};
