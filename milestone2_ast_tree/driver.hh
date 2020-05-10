#pragma once

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "scanner.h"
#include "parser.hh"
#include "program/Program.hpp"
#include "visitors/PrintVisitor.hpp"


class Driver {
 public:
  Driver();

  int parse(const std::string& f);
  void scan_begin();
  void scan_end();

  void PrintTree(const std::string& filename) const;

 public:
  friend class Scanner;

  Scanner scanner;
  yy::parser parser;

  std::shared_ptr<Program> program;
  std::map<std::string, int> variables;

  int result;
  bool trace_parsing;
  bool trace_scanning;
  yy::location location;
  std::string file;

 private:
  std::ifstream stream;

};
