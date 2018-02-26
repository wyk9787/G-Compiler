%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"
%defines
%define parser_class_name {parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#ifndef YY_NULLPTR
  #define YY_NULLPTR nullptr
#endif
#include <string>
#include <memory>
#include "token.hpp"
#include "expression.hpp"
class parser_driver;
// using namespace std;
}

// The parsing context
%param { parser_driver &driver }

// Request location tracking
%locations
%initial-action
{
  // Initialize the initial location.
  // NOTE: For some reasons unknown, I cannot access the filename when try to print error
  @$.begin.filename = @$.end.filename = &driver.file;
};

%define parse.trace
%define parse.error verbose

%code {
#include "parser_driver.h"
#include "token.hpp"
#include "expression.hpp"

// using namespace std;
}

%define api.token.prefix {TOK_}
%token
  END     0    "eof"
  PLUS         "+"
  SUBTRACT     "-"
  MULTIPLY     "*"
  DIVIDE       "/"
  LESS         "<"
  LEQ          "<="
  EQUAL        "=="
  GREATER      ">"
  GEQ          ">="
  LPAREN       "("
  RPAREN       ")"
  NAN          "NaN"
  IF           "if"
  ELSE         "else"
  THEN         "then"
  TRUE         "true"
  FALSE        "false"
  FUNC         "func"
  FUNC_BODY    "->"
  LET          "let"
  ASSIGN       "="
  IN           "in"
  REC          "rec"
;

%token <int> INT "int"
%token <double> DOUBLE "double"
%token <std::string> VAR "var"

%left "<=" "<" ">=" ">"
%left "=="
%left "+" "-"
%left "*" "/"

%type  < Shared_Exp > exp
%parse-param {Shared_Exp *ret}
%printer { yyoutput << $$->string_of_exp(); } exp;

%%

%start prog;

prog:
  exp "eof"             { *ret = $1; }

exp:
  "int"                           { Token t;
                                    t.id = Int;
                                    t.int_data = $1;
                                    $$ = std::make_shared<ELit>(t); }
| "double"                        { Token t;
                                    t.id = Float;
                                    t.float_data = $1;
                                    $$ = std::make_shared<ELit>(t); }
| "true"                          { Token t;
                                    t.id = Bool;
                                    t.bool_data = true;
                                    $$ = std::make_shared<ELit>(t); }
| "false"                         { Token t;
                                    t.id = Bool;
                                    t.bool_data = false;
                                    $$ = std::make_shared<ELit>(t); }
| "NaN"                           { Token t;
                                    t.id = NaN;
                                    $$ = std::make_shared<ELit>(t); }
| "var"                           { Token t;
                                    t.id = Var;
                                    t.var_data = $1;
                                    $$ = std::make_shared<ELit>(t); }
| "rec" "var" "var" "->" exp      { Token t;
                                    t.id = Fun;
                                    Func function;
                                    function.parameter = $3;
                                    function.e = $5;
                                    function.is_recursive = true;
                                    function.id = $2;
                                    t.func_data = function;
                                    $$ = std::make_shared<ELit>(t); }
| "func" "var" "->" exp           { Token t;
                                    t.id = Fun;
                                    Func function;
                                    function.parameter = $2;
                                    function.e = $4;
                                    t.func_data = function;
                                    $$ = std::make_shared<ELit>(t); }
| exp "+" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Plus, $1, $3); }
| exp "-" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Subtract, $1, $3); }
| exp "*" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Multiply, $1, $3); }
| exp "/" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Divide, $1, $3); }
| exp "<=" exp                    { $$ = std::make_shared<EOperator>(TokenKind::Leq, $1, $3); }
| exp "<" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Less, $1, $3); }
| exp "==" exp                    { $$ = std::make_shared<EOperator>(TokenKind::Equal, $1, $3); }
| exp ">" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Greater, $1, $3); }
| exp ">=" exp                    { $$ = std::make_shared<EOperator>(TokenKind::Geq, $1, $3); }
| exp "(" exp ")"                 { $$ = std::make_shared<EApp>($1, $3);}
| "let" "var" "=" exp "in" exp    { $$ = std::make_shared<ELet>($2, $4, $6); }
| "if" exp "then" exp "else" exp  { $$ = std::make_shared<EIf>($2, $4, $6); }

| "(" exp ")"                     { $$ = $2; }

%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const yy::parser::location_type& l, const std::string &m) { driver.error(l, m); }
