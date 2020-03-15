%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
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
    PRINT "System.out.println"
    LENGTH "length"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <int> expr
%nterm <int> integer_literal
%nterm <int> binary_operator

%printer { yyo << $$; } <*>;

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

method_declaration: "public" type "identifier" args_list "{" statement_list "}";

args_list: "(" ")"
         | "(" comma_formals_list ")";

comma_formals_list: formals
                  | comma_formals_list "," formals;

formals: type "identifier";

variable_declaration: type "identifier" ";";

type: simple_type | array_type;

simple_type: "int" | "boolean" | "void" | "type_identifier";

array_type: simple_type "[" "]";

type_identifier: "identifier";

statement: "assert" "(" expr ")" ";"
         | local_variable_declaration
         | "{" statement_list "}"
         | "if"  "(" expr ")" statement
         | "if"  "(" expr ")" statement "else" statement
         | "while" "(" expr ")" statement
         | PRINT "(" expr ")" ";" { std::cout << $3 << std::endl; }
         | lvalue "=" expr ";"
         | "return" expr ";"
         | method_invocation ";";

local_variable_declaration: variable_declaration;

method_invocation: expr "." "identifier" "(" comma_expr_list ")";

lvalue: "identifier" | "identifier" "[" expr "]";

comma_expr_list: expr
               | comma_expr_list "," expr;

expr: expr binary_operator expr { 
  switch($2) {
    case token::TOK_AND:     $$ = $1 && $3; break;
    case token::TOK_OR:      $$ = $1 || $3; break;
    case token::TOK_LESS:    $$ = $1 < $3;  break;
    case token::TOK_GREATER: $$ = $1 > $3;  break;
    case token::TOK_EQUAL:   $$ = $1 == $3; break;
    case token::TOK_PLUS:    $$ = $1 + $3;  break;
    case token::TOK_MINUS:   $$ = $1 - $3;  break;
    case token::TOK_STAR:    $$ = $1 * $3;  break;
    case token::TOK_SLASH:   $$ = $1 / $3;  break;
    case token::TOK_RMNDR:   $$ = $1 % $3;  break;
    default: break;
  }
}
    | expr "[" expr "]"              { /* TODO */ }
    | expr "." "length"              { /* TODO */ }
    | "new" simple_type "[" expr "]" { /* TODO */ }
    | "new" type_identifier "(" ")"  { /* TODO */ }
    | "!" expr                       { $$ = !$2; }
    | "(" expr ")"                   { $$ = $2; }
    | "identifier"                   { $$ = driver.variables[$1]; }
    | integer_literal                { $$ = $1; }
    | "this"                         { /* TODO */ }
    | "true"                         { $$ = true; }
    | "false"                        { $$ = false; }
    | method_invocation              { };

integer_literal: "number" { $$ = $1; }
               | "-" "number" { $$ = -$1; };

binary_operator: "&&" | "||" | "<" | ">" | "==" | "+" | "-" | "*" | "/" | "%";

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
