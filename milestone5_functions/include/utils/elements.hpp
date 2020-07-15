#pragma once

//debug
#include "debug.h"

// utils
#include "utils/BasicList.hpp"
// program
#include "program/Program.hpp"
#include "program/MainClass.hpp"
#include "program/ClassDeclList.hpp"
// statements
#include "statements/Statement.hpp"
#include "statements/AssertStmt.hpp"
#include "statements/LocalVarDeclStmt.hpp"
#include "statements/StmtListStmt.hpp"
#include "statements/ConditionalStmt.hpp"
#include "statements/PrintStmt.hpp"
#include "statements/StmtList.hpp"
#include "statements/AssignmentStmt.hpp"
#include "statements/ReturnStmt.hpp"
#include "statements/MethodStmt.hpp"
// expressions
#include "expressions/Expression.hpp"
#include "expressions/BinOpExpr.hpp"
#include "expressions/SubscriptExpr.hpp"
#include "expressions/LengthExpr.hpp"
#include "expressions/BoolConstExpr.hpp"
#include "expressions/IntExpr.hpp"
#include "expressions/NewExpr.hpp"
#include "expressions/NewArrayExpr.hpp"
#include "expressions/NotExpr.hpp"
#include "expressions/IdentExpr.hpp"
// declarations
#include "declarations/Decl.hpp"
#include "declarations/VarDecl.hpp"
#include "declarations/ClassDecl.hpp"
#include "declarations/DeclList.hpp"
// scopes
#include "scopes/Symbol.hpp"
#include "scopes/ScopeLayer.hpp"
#include "scopes/ScopeLayerTree.hpp"
// types
#include "types/Type.hpp"
#include "types/Object.hpp"
#include "types/Integer.hpp"
#include "types/Bool.hpp"
#include "types/Class.hpp"
#include "types/Array.hpp"
#include "types/UninitObject.hpp"
// value categories
#include "value_categories/Lvalue.hpp"
// functions
#include "functions/MethodInvocation.hpp"
#include "functions/CommaExprList.hpp"

