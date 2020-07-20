#include "utils/ExceptionGuy.hpp"

#include <exception>


ExceptionGuy& ExceptionGuy::GetInstance() {
  static ExceptionGuy instance;
  return instance;
}

void ExceptionGuy::Throw(std::string what, yy::location loc) {
  std::cerr << loc << ":" << std::endl;
  throw std::runtime_error("error: " + what);
}
