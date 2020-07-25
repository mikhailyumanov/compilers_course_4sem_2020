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
%nterm <std::shared_ptr<MethodInvocation>> method_invocation
%nterm <std::shared_ptr<CommaExprList>> comma_expr_list
%nterm <std::pair<Type, std::string>> formals
%nterm <std::pair<std::vector<Type>, std::vector<std::string>>> comma_formals_list
%nterm <std::pair<std::vector<Type>, std::vector<std::string>>> args_list
%nterm <std::shared_ptr<MethodDecl>> method_declaration

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
                   { $$ = std::make_shared<ClassDecl>($2, $4);
                     $$->SetLocation(driver.location);
                   }
                 | "class" "identifier" "extends" "identifier" "{"
                   declaration_list "}"
                   { $$ = std::make_shared<ClassDecl>($2, $6);
                     $$->SetLocation(driver.location);
                   }
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
             { $$ = $1; }
;

method_declaration: "public" type "identifier" args_list "{" statement_list "}"
                    { $$ = std::make_shared<MethodDecl>(
                          FunctionType($2, $4.first,$4.second), $3, $6); 
                      $$->SetLocation(driver.location);
                    }
;

args_list: "(" ")" { $$ = std::pair<std::vector<Type>,
                                    std::vector<std::string>>(); }
         | "(" comma_formals_list ")" { $$ = $2; }
;

comma_formals_list: formals
                    { $$ = std::pair<std::vector<Type>,
                                     std::vector<std::string>>();
                      $$.first.push_back($1.first);
                      $$.second.push_back($1.second); }
                  | comma_formals_list "," formals
                    { $$ = $1; $$.first.push_back($3.first);
                      $$.second.push_back($3.second); }
;

formals: type "identifier" { $$ = std::make_pair($1, $2); }
;

variable_declaration: type "identifier" ";"
                      { $$ = std::make_shared<VarDecl>($1, $2); 
                        $$->SetLocation(driver.location);
                      }
;

type: simple_type { $$ = Type{$1, false}; }
    | array_type  { $$ = Type{$1, true};  }
;

array_type: simple_type "[" "]" { $$ = $1; }
;

simple_type: "int" { $$ = "int"; }
           | "boolean" {$$ = "boolean"; }
           | "void" { $$ = "void"; }
           | type_identifier { $$ = $1; }
;

type_identifier: "identifier" { $$ = $1; }
;

statement: "assert" "(" expr ")" ";"
           { $$ = std::static_pointer_cast<Statement>(
              std::make_shared<AssertStmt>($3)); 
             $$->SetLocation(driver.location);
           }
         | "{" statement_list "}"
           { $$ = std::make_shared<StmtListStmt>($2); 
             $$->SetLocation(driver.location);
           }
         | "if"  "(" expr ")" statement
           { $$ = std::make_shared<IfStmt>($3, $5); 
             $$->SetLocation(driver.location);
           }
         | "if"  "(" expr ")" statement "else" statement
           { $$ = std::make_shared<IfElseStmt>($3, $5, $7); 
             $$->SetLocation(driver.location);
           }
         | "while" "(" expr ")" statement
           { $$ = std::make_shared<WhileStmt>($3, $5); 
             $$->SetLocation(driver.location);
           }
         | "System" "." "out" "." "println" "(" expr ")" ";"
           { $$ = std::make_shared<PrintStmt>($7); 
             $$->SetLocation(driver.location);
           }
         | lvalue "=" expr ";"
           { $$ = std::make_shared<AssignmentStmt>($1, $3); 
             $$->SetLocation(driver.location);
           }
         | local_variable_declaration
           { $$ = std::make_shared<LocalVarDeclStmt>($1);
             $$->SetLocation(driver.location);
           }

         // FIXME: such a terrible workaround, but stmt like
         // `Class[] class_array;` can't exist without it.
         | "identifier" "[" "]" "identifier" ";"
           { $$ = std::make_shared<LocalVarDeclStmt>(
                 std::make_shared<VarDecl>(Type{$1, true}, $4));
             $$->SetLocation(driver.location);
           }
        
         | "return" expr ";" 
           { $$ = std::make_shared<ReturnStmt>($2);
             $$->SetLocation(driver.location);
           }
         | method_invocation ";"
           { $$ = std::make_shared<MethodStmt>($1);
             $$->SetLocation(driver.location);
           }

;

local_variable_declaration: variable_declaration
                            { $$ = $1; }
;

method_invocation: expr "." "identifier" "(" comma_expr_list ")"
        { $$ = std::make_shared<MethodInvocation>($1, $3, $5);
          $$->SetLocation(driver.location);
        }
                 | expr "." "identifier" "(" ")"
        { $$ = std::make_shared<MethodInvocation>($1, $3, 
              std::make_shared<CommaExprList>());
          $$->SetLocation(driver.location);
        }
;

lvalue: "identifier" 
        { $$ = std::make_shared<Lvalue>($1);
          $$->SetLocation(driver.location);
        }
      | "identifier" "[" expr "]" 
        { $$ = std::make_shared<Lvalue>($1, $3);
          $$->SetLocation(driver.location);
        }

;

comma_expr_list: expr { $$ = std::make_shared<CommaExprList>(); $$->AddItem($1); }
               | comma_expr_list "," expr { $$ = $1; $$->AddItem($3); }
;


%left "&&" "||";
%left "==" "!";
%left "<" ">";
%left "+" "-";
%left "*" "/" "%";

expr: expr AND    expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_AND     , $3);
   $$->SetLocation(driver.location);
  }
   | expr OR      expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_OR      , $3);
   $$->SetLocation(driver.location);
  }
   | expr LESS    expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_LESS    , $3);
   $$->SetLocation(driver.location);
  }
   | expr GREATER expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_GREATER , $3);
   $$->SetLocation(driver.location);
  }
   | expr EQUAL   expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_EQUAL   , $3);
   $$->SetLocation(driver.location);
  }
   | expr PLUS    expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_PLUS    , $3);
   $$->SetLocation(driver.location);
  }
   | expr MINUS   expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_MINUS   , $3);
   $$->SetLocation(driver.location);
  }
   | expr STAR    expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_STAR    , $3);
   $$->SetLocation(driver.location);
  }
   | expr SLASH   expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_SLASH   , $3);
   $$->SetLocation(driver.location);
  }
   | expr RMNDR   expr
  {$$ = std::make_shared<BinOpExpr>($1, BinOpExpr::Operation::OP_RMNDR   , $3);
   $$->SetLocation(driver.location);
  }

    | expr "[" expr "]"
      { $$ = std::make_shared<SubscriptExpr>($1, $3);
        $$->SetLocation(driver.location);
      }
    | expr "." "length"
      { $$ = std::make_shared<LengthExpr>($1);
        $$->SetLocation(driver.location);
      }
    | "new" simple_type "[" expr "]"
      { $$ = std::make_shared<NewArrayExpr>($2, $4);
        $$->SetLocation(driver.location);
      }
    | "new" type_identifier "(" ")"
      { $$ = std::make_shared<NewExpr>($2);
        $$->SetLocation(driver.location);
      }
    | "(" expr ")"
      { $$ = $2; }

    | "identifier"
      { $$ = std::make_shared<IdentExpr>($1);
        $$->SetLocation(driver.location);
      }
    | integer_literal
      { $$ = std::make_shared<IntExpr>($1);
        $$->SetLocation(driver.location);
      }
    | "this"
      { $$ = std::make_shared<ThisExpr>();
        $$->SetLocation(driver.location);
      }
    | "true"
      { $$ = std::make_shared<TrueExpr>();
        $$->SetLocation(driver.location);
      }
    | "false"
      { $$ = std::make_shared<FalseExpr>();
        $$->SetLocation(driver.location);
      }
    | method_invocation
      { $$ = std::make_shared<MethodExpr>($1);
        $$->SetLocation(driver.location);
      }
    | "!" expr
      { $$ = std::make_shared<NotExpr>($2);
        $$->SetLocation(driver.location);
      }

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
