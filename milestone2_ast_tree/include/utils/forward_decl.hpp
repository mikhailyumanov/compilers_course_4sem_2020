#pragma once

// utils
class BasicList;
// program
class Program;
class MainClass;
class ClassDeclList;
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
class StmtList;
// expressions
class Expression;
class BinOpExpr;
class TrueExpr;
class FalseExpr;
class IntExpr;
class NewExpr;
class NotExpr;
class IdentExpr;
// declarations
class Decl;
class VarDecl;
class ClassDecl;
class DeclList;
// value categories
class Lvalue;

struct Type {
  std::string type;
  bool is_array;
} ;
