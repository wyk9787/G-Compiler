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

%precedence "else"
%precedence "then"
%precedence "if"
%left "<=" "<" ">=" ">"
%left "=="
%left "+" "-"
%left "*" "/"
%left "(" ")"

%type  < Shared_Exp > exp
%parse-param {Shared_Exp *ret}
%printer { yyoutput << $$->string_of_exp(); } exp;

%%

%start prog;

prog:
  exp "eof"             { *ret = $1; }

exp:
  "int"                           { $$ = std::make_shared<ELit>(true, $1, 0, false); }
| "double"                        { $$ = std::make_shared<ELit>(false, 0, $1, false); }
| "true"                          { $$ = std::make_shared<EBool>(true); }
| "false"                         { $$ = std::make_shared<EBool>(false); }
| "NaN"                           { $$ = std::make_shared<ELit>(false, 0, 0, true); }
| "var"                           { $$ = std::make_shared<EVar>($1); }
| "rec" "var" "var" "->" exp      { $$ = std::make_shared<EFunc>($3, $5, true, $2); }
| "func" "var" "->" exp           { $$ = std::make_shared<EFunc>($2, $4, false, ""); }
| exp "+" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Plus, $1, $3); }
| exp "-" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Subtract, $1, $3); }
| exp "*" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Multiply, $1, $3); }
| exp "/" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Divide, $1, $3); }
| exp "<=" exp                    { $$ = std::make_shared<EComp>(TokenKind::Leq, $1, $3); }
| exp "<" exp                     { $$ = std::make_shared<EComp>(TokenKind::Less, $1, $3); }
| exp "==" exp                    { $$ = std::make_shared<EComp>(TokenKind::Equal, $1, $3); }
| exp ">" exp                     { $$ = std::make_shared<EComp>(TokenKind::Greater, $1, $3); }
| exp ">=" exp                    { $$ = std::make_shared<EComp>(TokenKind::Geq, $1, $3); }
| exp "(" exp ")"                 { $$ = std::make_shared<EApp>($1, $1, $3, false, false);}
| "let" "var" "=" exp "in" exp    { $$ = std::make_shared<ELet>($2, $4, $6, false); }
| "if" exp "then" exp "else" exp  { $$ = std::make_shared<EIf>($2, $4, $6); }
| "(" exp ")"                     { $$ = $2; }

%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const yy::parser::location_type& l, const std::string &m) { driver.error(l, m); }
