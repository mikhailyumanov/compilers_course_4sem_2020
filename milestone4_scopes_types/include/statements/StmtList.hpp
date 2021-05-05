#pragma once

#include "utils/BasicList.hpp"

class StmtList: public BasicList,
  public std::enable_shared_from_this<StmtList> {};
