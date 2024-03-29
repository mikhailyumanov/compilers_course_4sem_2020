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

    include/expressions/BinOpExpr.cpp
    include/expressions/BoolConstExpr.cpp
    include/expressions/IntExpr.cpp
    include/expressions/NewExpr.cpp
    include/expressions/NotExpr.cpp
    include/expressions/IdentExpr.cpp

    include/utils/BasicList.cpp

    include/declarations/VarDecl.cpp
    include/declarations/ClassDecl.cpp

    include/value_categories/Lvalue.cpp

    include/visitors/PrintVisitor.cpp
    include/visitors/Interpreter.cpp
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
