#pragma once

#include <string>

#include "parser.hh"


class ExceptionGuy {
 public:
  static ExceptionGuy& GetInstance();

  void Throw(std::string what, yy::location loc);
  void Throw(std::string what);
};
