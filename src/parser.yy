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
#include "type.hpp"
#include "global.hpp"
class parser_driver;
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
#include "type.hpp"
#include "interpreter.hpp"
}

%define api.token.prefix {TOK_}
%token
  EOF     0    "eof"
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
  LET_ASSIGN   "="
  IN           "in"
  REC          "rec"
  COL          ":"
  LBRA         "["
  RBRA         "]"
  UNIT         "()"
  FST          "fst"
  SND          "snd"
  COMMA        ","
  LCURLY       "{"
  RCURLY       "}"
  CONS         "::"
  CAR          "car"
  CDR          "cdr"
  EMPTY        "empty"
  DEREF        "!"
  REF          "ref"
  ASSIGN       ":="
  SEQ          ";"
  WHILE        "while"
  DO           "do"
  END          "end"
  INCLUDE      "include"
  POND         "#"
  DEF          "def"
  ARROW        "=>"
  STRUCT       "struct"
  DOT          "."
;

%token <int> INT "int"
%token <double> DOUBLE "double"
%token <std::string> VAR "var"
%token <Shared_TInt> TINT "tint"
%token <Shared_TFloat> TFLOAT "tfloat"
%token <Shared_TBool> TBOOL "tbool"
%token <Shared_TUnit> TUNIT "tunit"
%token <Shared_TStruct> TSTRUCT "tstruct"

%right "!" "ref"
%left ";"
%left ":="
%precedence "if" "then" "else"
%right "->" "::"
%left "<=" "<" ">=" ">" "=="
%left "+" "-"
%left "*" "/"
%left "."
%left "(" ")"


%type  <Shared_Exp> exp
%type  <Shared_Typ> typ
%parse-param {Shared_Exp *ret}
%printer { yyoutput << $$->string_of_exp(); } exp;

%%

%start prog;

prog:
  exp "eof"                       { *ret = $1; }
;

struct_statement_list: struct_statement
| struct_statement_list struct_statement
;

struct_statement:
  typ "var" "=>" exp ","     { global_struct_data.insert({$2, $4});
                               global_struct_type.insert({$2, $1}); }
;

exp:
  "int"                           { $$ = std::make_shared<ELit>(true, $1, 0, false); }
| "double"                        { $$ = std::make_shared<ELit>(false, 0, $1, false); }
| "true"                          { $$ = std::make_shared<EBool>(true); }
| "false"                         { $$ = std::make_shared<EBool>(false); }
| "NaN"                           { $$ = std::make_shared<ELit>(false, 0, 0, true); }
| "var"                           { $$ = std::make_shared<EVar>($1); }
| "()"                            { $$ = std::make_shared<EUnit>(); }
| "rec" "var" "[" "var" ":" typ "]" ":" typ "->" exp
                                  { $$ = std::make_shared<EFunc>($4, $6, $9, $11, true, $2); }
| "func" "[" "var" ":" typ "]" ":" typ "->" exp
                                  { $$ = std::make_shared<EFunc>($3, $5, $8, $10, false, ""); }
| exp "+" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Plus, $1, $3); }
| exp "-" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Subtract, $1, $3); }
| exp "*" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Multiply, $1, $3); }
| exp "/" exp                     { $$ = std::make_shared<EOperator>(TokenKind::Divide, $1, $3); }
| exp "<=" exp                    { $$ = std::make_shared<EComp>(TokenKind::Leq, $1, $3); }
| exp "<" exp                     { $$ = std::make_shared<EComp>(TokenKind::Less, $1, $3); }
| exp "==" exp                    { $$ = std::make_shared<EComp>(TokenKind::Equal, $1, $3); }
| exp ">" exp                     { $$ = std::make_shared<EComp>(TokenKind::Greater, $1, $3); }
| exp ">=" exp                    { $$ = std::make_shared<EComp>(TokenKind::Geq, $1, $3); }
| exp "(" exp ")"                 { $$ = std::make_shared<EApp>($1, $3); }
| "(" exp "," exp ")"             { $$ = std::make_shared<EPair>($2, $4); }
| "fst" "(" exp ")"               { $$ = std::make_shared<EFst>($3); }
| "snd" "(" exp ")"               { $$ = std::make_shared<ESnd>($3); }
| "car" "(" exp ")"               { $$ = std::make_shared<ECar>($3); }
| "cdr" "(" exp ")"               { $$ = std::make_shared<ECdr>($3); }
| "empty" "(" exp ")"             { $$ = std::make_shared<EEmpty>($3); }
| exp "::" exp                    { $$ = std::make_shared<ECons>($1, $3); }
| "{" "}" ":" typ                 { std::vector<Shared_Exp> v;
                                    $$ = std::make_shared<EList>(v, $4); }
| "ref" "(" exp ")"               { $$ = std::make_shared<ERef>($3); }
| "!" "(" exp ")"                 { $$ = std::make_shared<EDeref>($3); }
| exp ":=" exp                    { $$ = std::make_shared<EAssign>($1, $3); }
| exp ";" exp                     { $$ = std::make_shared<ESeq>($1, $3); }
| "let" "[" "var" ":" typ "]" "=" exp "in" exp
                                  { $$ = std::make_shared<ELet>($3, $5, $8, $10); }
| "if" "(" exp ")" "{" exp "}" "else" "{" exp "}"
                                  { $$ = std::make_shared<EIf>($3, $6, $10); }
| "while" "(" exp ")" "{" exp "}" { $$ = std::make_shared<EWhile>($3, $6, $3); }
| "(" exp ")" %prec "->"          { $$ = $2; }
| typ "var" "=" "{" exp "}"       { $$ = std::make_shared<EDef>($2, $5, $1); }
| "struct" "{" struct_statement_list "}"
                                  { $$ = std::make_shared<EStruct>(global_struct_data,        global_struct_type);
                                    global_struct_data.clear();
                                    global_struct_type.clear(); }
| exp  "." "var"                  { $$ =  std::make_shared<EDot>($1, $3); }
;

typ:
  "tint"                          { $$ = $1; }
| "tfloat"                        { $$ = $1; }
| "tbool"                         { $$ = $1; }
| "tunit"                         { $$ = $1; }
| "tstruct"                           { $$ = $1; }
| typ "->" typ                    { $$ = std::make_shared<TFunc>($1, $3); }
| typ "*" typ  %prec "->"         { $$ = std::make_shared<TPair>($1, $3); }
| "{" typ "}"                     { $$ = std::make_shared<TList>($2); }
| "<" typ ">"                     { $$ = std::make_shared<TRef>($2); }
| "[" typ "]"                     { $$ = $2; }

%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const yy::parser::location_type& l, const std::string &m) { driver.error(l, m); }
