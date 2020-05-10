#pragma once

// utils
class BasicList;
// program
class Program;
class MainClass;
using ClassDeclList = BasicList;
// statements
class Statement;
class AssertStmt;
class LocalVarDeclStmt;
class StmtListStmt;
class IfStmt;
class IfElseStmt;
class WhileStmt;
class PrintStmt;
class AssignmentStmt;
using StmtList = BasicList;
// expressions
class Expression;
class BinOpExpr;
class TrueExpr;
class FalseExpr;
class IntExpr;
class NewExpr;
class NotExpr;
// declarations
class Decl;
class VarDecl;
class ClassDecl;
using DeclList = BasicList;
// value categories
class Lvalue;

struct Type {
  std::string type;
  bool is_array;
} ;
