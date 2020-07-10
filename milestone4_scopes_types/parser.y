%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <functional>
    #include <memory>
    #include <string>

    #include "utils/forward_decl.hpp"

    class Scanner;
    class Driver;
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    // include nodes
    #include "utils/elements.hpp"


    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"

// operators
%token
    ASSIGN "="
    <int> MINUS "-"
    <int> PLUS "+"
    <int> STAR "*"
    <int> SLASH "/"
    <int> AND "&&"
    <int> OR "||"
    <int> LESS "<"
    <int> GREATER ">"
    <int> EQUAL "=="
    <int> RMNDR "%"

// syntax
%token
    NOT "!"
    LPAREN "("
    RPAREN ")"
    LPARENSQR "["
    RPARENSQR "]"
    LPARENCRV "{"
    RPARENCRV "}"
    DOT "."
    COLON ","
    SEMICOLON ";"

// keywords
%token
    NEW "new"
    THIS "this"
    TRUE "true"
    FALSE "false"
    IF "if"
    ELSE "else"
    WHILE "while"
    ASSERT "assert"
    CLASS "class"
    EXTENDS "extends"
    PUBLIC "public"
    STATIC "static"
    RETURN "return"

// types
%token
    INT "int"
    BOOL "boolean"
    VOID "void"

// other
%token
    MAIN "main"
    SYSTEM "System"
    OUT "out"
    PRINTLN "println"
    LENGTH "length"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <int> integer_literal
%nterm <int> binary_operator
%nterm <std::shared_ptr<Lvalue>> lvalue
%nterm <Type> type
%nterm <std::string> type_identifier
%nterm <std::string> simple_type
%nterm <std::string> array_type

%nterm <std::shared_ptr<Program>> program
%nterm <std::shared_ptr<ClassDeclList>> class_declaration_list
%nterm <std::shared_ptr<MainClass>> main_class
%nterm <std::shared_ptr<ClassDecl>> class_declaration
%nterm <std::shared_ptr<StmtList>> statement_list
%nterm <std::shared_ptr<DeclList>> declaration_list
%nterm <std::shared_ptr<Decl>> declaration
%nterm <std::shared_ptr<VarDecl>> variable_declaration
%nterm <std::shared_ptr<Statement>> statement
%nterm <std::shared_ptr<VarDecl>> local_variable_declaration
%nterm <std::shared_ptr<Expression>> expr

//%printer { yyo << $$; } <*>;

%%
%start program;

program: main_class 
         { $$ = std::make_shared<Program>($1); driver.program = $$; }
       | main_class class_declaration_list
         { $$ = std::make_shared<Program>($1, $2); driver.program = $$; }
;

class_declaration_list: class_declaration
                        { $$ = std::make_shared<ClassDeclList>();
                          $$->AddItem($1); }
                      | class_declaration_list class_declaration
                        { $$ = $1; $$->AddItem($2); }
;

main_class: "class" "identifier" "{"
            "public" "static" "void" "main" "(" ")" "{" statement_list "}" "}"
            { $$ = std::make_shared<MainClass>($11); }
;

class_declaration: "class" "identifier" "{" declaration_list "}"
                   { $$ = std::make_shared<ClassDecl>($2, $4); }
                 | "class" "identifier" "extends" "identifier" "{"
                   declaration_list "}"
                   { $$ = std::make_shared<ClassDecl>($2, $6); }
;

statement_list: statement
                { $$ = std::make_shared<StmtList>(); $$->AddItem($1); }
              | statement_list statement
                { $$ = $1; $$->AddItem($2); }
;

declaration_list : declaration
                   { $$ = std::make_shared<DeclList>(); $$->AddItem($1); }
                 | declaration_list declaration
                   { $$ = $1; $$->AddItem($2); }
;

declaration: variable_declaration
             { $$ = $1; }
           | method_declaration
//             { $$ = $1; }
;

method_declaration: "public" type "identifier" args_list "{"
                  statement_list "}"
;

args_list: "(" ")"
         | "(" comma_formals_list ")"
;

comma_formals_list: formals
                  | comma_formals_list "," formals
;

formals: type "identifier"       
;

variable_declaration: type "identifier" ";"
                      { $$ = std::make_shared<VarDecl>($1, $2); }
//                    { driver.variables[$2] = 
//                          std::make_pair(std::vector<int>(), $1.second); }
;

type: simple_type { $$ = Type{$1, false}; } //{ $$ = std::make_pair($1, 0); } 
    | array_type  { $$ = Type{$1, true};  } //{ $$ = std::make_pair($1, 1); }
;

simple_type: "int" { $$ = "int"; }
           | "boolean" {$$ = "boolean"; }
           | "void" { $$ = "void"; }
           | type_identifier{ $$ = $1; }
;

array_type: simple_type "[" "]" { $$ = $1; }
;

type_identifier: "identifier" { $$ = $1; }
;

statement: "assert" "(" expr ")" ";"
           { $$ = std::static_pointer_cast<Statement>(
              std::make_shared<AssertStmt>($3)); }
         | local_variable_declaration
           { $$ = std::make_shared<LocalVarDeclStmt>($1); }
         | "{" statement_list "}"
           { $$ = std::make_shared<StmtListStmt>($2); }
         | "if"  "(" expr ")" statement
           { $$ = std::make_shared<IfStmt>($3, $5); }
         | "if"  "(" expr ")" statement "else" statement
           { $$ = std::make_shared<IfElseStmt>($3, $5, $7); }
         | "while" "(" expr ")" statement
           { $$ = std::make_shared<WhileStmt>($3, $5); }
         | "System" "." "out" "." "println" "(" expr ")" ";"
           { $$ = std::make_shared<PrintStmt>($7); }
         | lvalue "=" expr ";"
           { $$ = std::make_shared<AssignmentStmt>($1, $3); }
         | "return" expr ";"
         | method_invocation ";";

local_variable_declaration: variable_declaration
                            { $$ = $1; }
;

method_invocation: expr "." "identifier" "(" comma_expr_list ")" 
;

lvalue: "identifier" 
        { $$ = std::make_shared<Lvalue>($1); }
      | "identifier" "[" expr "]" 
        { $$ = std::make_shared<Lvalue>($1, $3); }
;

comma_expr_list: expr
               | comma_expr_list "," expr
;


%left "&&" "||";
%left "==" "!";
%left "<" ">";
%left "+" "-";
%left "*" "/";

expr: expr AND    expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_AND     , $3);}
   | expr OR      expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_OR      , $3);}
   | expr LESS    expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_LESS    , $3);}
   | expr GREATER expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_GREATER , $3);}
   | expr EQUAL   expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_EQUAL   , $3);}
   | expr PLUS    expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_PLUS    , $3);}
   | expr MINUS   expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_MINUS   , $3);}
   | expr STAR    expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_STAR    , $3);}
   | expr SLASH   expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_SLASH   , $3);}
   | expr RMNDR   expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_RMNDR   , $3);}

    | expr "[" expr "]"
      { $$ = std::make_shared<SubscriptExpr>($1, $3); }

    | expr "." "length"
      { $$ = std::make_shared<LengthExpr>($1); }

    | "new" simple_type "[" expr "]"
      { $$ = std::make_shared<NewArrayExpr>($2, $4); }

    | "new" type_identifier "(" ")"
      { $$ = std::make_shared<NewExpr>($2); }

    | "(" expr ")"
      { $$ = $2; }

    | "identifier"
      { $$ = std::make_shared<IdentExpr>($1); }

    | integer_literal
      { $$ = std::make_shared<IntExpr>($1); }

    | "this"                         { /* TODO */ }

    | "true"
      { $$ = std::make_shared<TrueExpr>(); }

    | "false"
      { $$ = std::make_shared<FalseExpr>(); }

    | method_invocation              { };

    | "!" expr
      { $$ = std::make_shared<NotExpr>($2); }


integer_literal: "number" { $$ = $1; }
               | "-" "number" { $$ = -$2; };

binary_operator: "&&" | "||" | "<" | ">" | "=="
               | "+"  | "-"  | "*" | "/" | "%";

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
