%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <functional>     
    #include <string>
    class Scanner;
    class Driver;
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

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
%nterm <std::pair<std::vector<int>, bool>> expr
%nterm <int> integer_literal
%nterm <int> binary_operator
%nterm <std::pair<std::string, int>> lvalue
%nterm <std::pair<std::string, bool>> type
%nterm <std::string> simple_type
%nterm <std::string> array_type

//%printer { yyo << $$; } <*>;

%%
%start program;

program: main_class
       | main_class class_declaration_list;

class_declaration_list: class_declaration
                      | class_declaration_list class_declaration;

main_class: "class" "identifier" "{"
            "public" "static" "void" "main" "(" ")" "{" statement_list "}" "}";

class_declaration: "class" "identifier" "{" declaration_list "}"
                 | "class" "identifier" "extends" "identifier" "{"
                   declaration_list "}";

statement_list: statement
              | statement_list statement;

declaration_list : declaration
                 | declaration_list declaration;

declaration: variable_declaration
           | method_declaration;

method_declaration: "public" type "identifier" args_list "{"
                  statement_list "}";

args_list: "(" ")"
         | "(" comma_formals_list ")";

comma_formals_list: formals
                  | comma_formals_list "," formals;

formals: type "identifier";

variable_declaration: type "identifier" ";"
                    { driver.variables[$2] = 
                          std::make_pair(std::vector<int>(), $1.second); };

type: simple_type { $$ = std::make_pair($1, 0); } 
    | array_type  { $$ = std::make_pair($1, 1); };

simple_type: "int" | "boolean" | "void" | "type_identifier";

array_type: simple_type "[" "]" { $$ = $1; };

type_identifier: "identifier";

statement: "assert" "(" expr ")" ";"
         | local_variable_declaration
         | "{" statement_list "}"
         | "if"  "(" expr ")" statement
         | "if"  "(" expr ")" statement "else" statement
         | "while" "(" expr ")" statement
         | "System" "." "out" "." "println" "(" expr ")" ";"
           { std::cout << $7.first[0] << std::endl; }
         | lvalue "=" expr ";"
           { if ($1.second == -1) driver.variables[$1.first] = $3;
             else driver.variables[$1.first].first[$1.second] = $3.first[0]; }
         | "return" expr ";"
         | method_invocation ";";

local_variable_declaration: variable_declaration;

method_invocation: expr "." "identifier" "(" comma_expr_list ")";

lvalue: "identifier"              { $$ = std::make_pair($1, -1); }
      | "identifier" "[" expr "]" { $$ = std::make_pair($1, $3.first[0]); };

comma_expr_list: expr
               | comma_expr_list "," expr;

expr: expr binary_operator expr { 
    int tmp = 0;
  switch($2) {
    case token::TOK_AND:     tmp = $1.first[0] && $3.first[0]; break;
    case token::TOK_OR:      tmp = $1.first[0] || $3.first[0]; break;
    case token::TOK_LESS:    tmp = $1.first[0] <  $3.first[0]; break;
    case token::TOK_GREATER: tmp = $1.first[0] >  $3.first[0]; break;
    case token::TOK_EQUAL:   tmp = $1.first[0] == $3.first[0]; break;
    case token::TOK_PLUS:    tmp = $1.first[0] +  $3.first[0]; break;
    case token::TOK_MINUS:   tmp = $1.first[0] -  $3.first[0]; break;
    case token::TOK_STAR:    tmp = $1.first[0] *  $3.first[0]; break;
    case token::TOK_SLASH:   tmp = $1.first[0] /  $3.first[0]; break;
    case token::TOK_RMNDR:   tmp = $1.first[0] %  $3.first[0]; break;
    default: break;
  }
  $$ = std::make_pair(std::vector<int>{tmp}, 0);
}
    | expr "[" expr "]"
      { $$ = std::make_pair(std::vector<int>{$1.first[$3.first[0]]}, 0); }

    | expr "." "length" { $$ = std::make_pair(std::vector<int>{(int)$1.first.size()}, 0); }

    | "new" simple_type "[" expr "]"
      { $$ = std::make_pair(std::vector<int>($4.first[0]), 1); }

    | "new" type_identifier "(" ")"
      { $$ = std::make_pair(std::vector<int>(1), 0); }

    | "!" expr
      { $$ = std::make_pair(std::vector<int>{!$2.first[0]}, 0); }

    | "(" expr ")"                   { $$ = $2; }

    | "identifier"                   { $$ = driver.variables[$1]; }

    | integer_literal
      { $$ = std::make_pair(std::vector<int>{$1}, 0); }

    | "this"                         { /* TODO */ }

    | "true"
      { $$ = std::make_pair(std::vector<int>{1}, 0); }

    | "false"
      { $$ = std::make_pair(std::vector<int>{0}, 0); }

    | method_invocation              { };

integer_literal: "number" { $$ = $1; }
               | "-" "number" { $$ = -$2; };

binary_operator: "&&" | "||" | "<" | ">" | "=="
               | "+"  | "-"  | "*" | "/" | "%";

/*
unit: assignments exp { driver.result = $2; };

assignments:
    %empty {}
    | assignments assignment {};

assignment:
    "identifier" "=" exp {
        driver.variables[$1] = $3;
        // std::cout << drv.location.begin.line
        //           << "-" << drv.location.end.line << std::endl;
    };

%left "+" "-";
%left "*" "/";

exp:
    "number"
    | "identifier" {$$ = driver.variables[$1];}
    | exp "+" exp {$$ = $1 + $3; }
    | exp "-" exp {$$ = $1 - $3; }
    | exp "*" exp {$$ = $1 * $3; }
    | exp "/" exp {$$ = $1 / $3; }
    | "(" exp ")" {$$ = $2; };
*/
%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
