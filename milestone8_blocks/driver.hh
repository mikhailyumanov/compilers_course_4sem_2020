#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "scanner.h"
#include "parser.hh"
#include "program/Program.hpp"

#include "visitors/PrintVisitor.hpp"
#include "visitors/Interpreter.hpp"
#include "visitors/SymbolTreeVisitor.hpp"
#include "visitors/IrtreeBuildVisitor.hpp"

#include "irtree/blocks/Block.hpp"
#include "irtree/blocks/BlockTree.hpp"

#include "irtree/elements.hpp"


class Driver {
 public:
  Driver();

  int parse(const std::string& f);
  void scan_begin();
  void scan_end();

  void BuildSymbolTree(const std::string& filename) const;
  void PrintTree(const std::string& filename) const;
  void PrintIrtree(const std::string& filename) const;
  void PrintBlockTree(const std::string& filename) const;
  int Eval() const;

 public:
  friend class Scanner;

  Scanner scanner;
  yy::parser parser;

  std::shared_ptr<Program> program;

  int result;
  bool trace_parsing;
  bool trace_scanning;
  bool trace_tree_building;
  std::string tree_output;

  yy::location location;
  std::string file;

 private:
  std::ifstream stream;

};