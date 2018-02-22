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
using namespace std;
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

using namespace std;
}

%define api.token.prefix {TOK_}
%token
  END     0    "eof"
  PLUS         "+"
  SUBTRACT     "-"
  MULTIPLY     "*"
  DIVIDE       "/"
  LEQ          "<="
  LPAREN       "("
  RPAREN       ")"
  NAN          "NaN"
  IF           "if"
  ELSE         "else"
  THEN         "then"
  TRUE         "true"
  FALSE        "false"
;

%token <int> INT "int"
%token <double> DOUBLE "double"
%type  < Shared_Exp > exp
%parse-param {Shared_Exp *ret}
%printer { yyoutput << $$->string_of_exp(); } exp;


%%

%left "<=";
%left "+" "-";
%left "*" "/";

%start prog;

prog:
  exp "eof"             { *ret = $1; }

exp:
  "int"                  { Token t;
                           t.id = Num_Int;
                           t.int_data = $1;
                           $$ = make_shared<ELit>(t); }
| "double"               { Token t;
                           t.id = Num_Float;
                           t.float_data = $1;
                           $$ = make_shared<ELit>(t); }
| "true"                 { Token t;
                           t.id = True;
                           t.bool_data = true;
                           $$ = make_shared<ELit>(t); }
| "false"                { Token t;
                           t.id = False;
                           t.bool_data = false;
                           $$ = make_shared<ELit>(t); }
| "NaN"                  { Token t;
                           t.id = Lit_NaN;
                           $$ = make_shared<ELit>(t); }

| exp "+" exp            { $$ = make_shared<EOperator>(TokenKind::Plus, $1, $3); }
| exp "-" exp            { $$ = make_shared<EOperator>(TokenKind::Subtract, $1, $3); }
| exp "*" exp            { $$ = make_shared<EOperator>(TokenKind::Multiply, $1, $3); }
| exp "/" exp            { $$ = make_shared<EOperator>(TokenKind::Divide, $1, $3); }
| exp "<=" exp           { $$ = make_shared<EOperator>(TokenKind::Less_Than, $1, $3); }
| "if" exp "then" exp "else" exp
                         { $$ = make_shared<EIf>($2, $4, $6); }
| "(" exp ")"            { $$ = $2; }

%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const yy::parser::location_type& l, const std::string &m) { driver.error(l, m); }
