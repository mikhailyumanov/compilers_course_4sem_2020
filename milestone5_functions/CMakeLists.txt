cmake_minimum_required(VERSION 3.10)
project(Project)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(
    HEADERS
    ${Project_SOURCE_DIR}/driver.hh
    ${Project_SOURCE_DIR}/parser.hh
    )

BISON_TARGET(
    MyParser
    parser.y
    ${Project_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${Project_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScanner
    scanner.l
    ${Project_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(
    SOURCES
    driver.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
    include/program/Program.cpp
    include/program/MainClass.cpp

    include/statements/PrintStmt.cpp
    include/statements/AssertStmt.cpp
    include/statements/LocalVarDeclStmt.cpp
    include/statements/StmtListStmt.cpp
    include/statements/ConditionalStmt.cpp
    include/statements/PrintStmt.cpp
    include/statements/AssignmentStmt.cpp
    include/statements/LocalVarDeclStmt.cpp
    include/statements/ReturnStmt.cpp
    include/statements/MethodStmt.cpp

    include/expressions/BinOpExpr.cpp
    include/expressions/BoolConstExpr.cpp
    include/expressions/SubscriptExpr.cpp
    include/expressions/LengthExpr.cpp
    include/expressions/IntExpr.cpp
    include/expressions/NewExpr.cpp
    include/expressions/NewArrayExpr.cpp
    include/expressions/NotExpr.cpp
    include/expressions/IdentExpr.cpp
    include/expressions/MethodExpr.cpp
    include/expressions/ThisExpr.cpp

    include/utils/BasicList.cpp

    include/declarations/VarDecl.cpp
    include/declarations/MethodDecl.cpp
    include/declarations/ClassDecl.cpp

    include/scopes/Symbol.cpp
    include/scopes/ScopeLayer.cpp
    include/scopes/ScopeLayerTree.cpp

    include/types/Type.cpp
    include/types/FunctionType.cpp
    include/types/Object.cpp
    include/types/Integer.cpp
    include/types/Bool.cpp
    include/types/Class.cpp
    include/types/Array.cpp
    include/types/UninitObject.cpp
    include/types/Function.cpp

    include/value_categories/Lvalue.cpp

    include/functions/MethodInvocation.cpp
    include/functions/Frame.cpp
    include/functions/FunctionTable.cpp
    include/functions/FunctionStorage.cpp

    include/types/constructor/Constructor.cpp
    include/types/constructor/IntegerBuilder.cpp
    include/types/constructor/BoolBuilder.cpp
    include/types/constructor/ClassBuilder.cpp

    include/visitors/PrintVisitor.cpp
    include/visitors/Interpreter.cpp
    include/visitors/TemplateVisitor.cpp
    include/visitors/SymbolTreeVisitor.cpp

    debug.cpp
)

add_executable(
    Project
    ${Project_SOURCE_DIR}/main.cpp
    ${SOURCES}
)

target_include_directories(Project PRIVATE ${Project_SOURCE_DIR})
target_include_directories(Project PRIVATE 
  ${Project_SOURCE_DIR}/include
)
