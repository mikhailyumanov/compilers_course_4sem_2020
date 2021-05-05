#pragma once

#include "utils/BasicList.hpp"

class CommaExprList: public BasicList,
  public std::enable_shared_from_this<CommaExprList> {};
