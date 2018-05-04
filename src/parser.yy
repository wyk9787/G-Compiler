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
using namespace fexp;
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
  FUNC_BODY    "->"
  LET          "let"
  LET_ASSIGN   "="
  IN           "in"
  REC          "rec"
  COL          ":"
  LBRA         "["
  RBRA         "]"
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
  END_DECL     ";;"
;

%token <int> INT "int"
%token <double> DOUBLE "double"
%token <std::string> VAR "var"
%token <Shared_TInt> TINT "tint"
%token <Shared_TFloat> TFLOAT "tfloat"
%token <Shared_TBool> TBOOL "tbool"
%token <Shared_TUnit> TUNIT "tunit"
%token <Shared_TStruct> TSTRUCT "tstruct"

%right "->" "::"
%right "!" "ref"
%left ";"
%left ":="
%precedence "if" "then" "else"
%left "<=" "<" ">=" ">" "=="
%left "+" "-"
%left "*" "/"
%left "."
%left "(" ")"

%type  <Shared_Exp> exp
%type  <Shared_Exp> exp_ops
%type  <Shared_Exp> exp_base
%type  <Shared_Exp> exp_app
%type  <Shared_Typ> typ
%type  <arg_t> formal
%type  <arglist_t> formallist
%type  <std::vector<Shared_Exp>> expslist
%parse-param {Shared_Exp *ret}
%printer { yyoutput << $$->string_of_exp(); } exp;

%%

%start prog;

prog:
  decllist "eof"                  {
                                    std::vector<Shared_Exp> v;
                                    v.push_back(std::make_shared<ELit>(true, 1, 0, false));
                                    *ret = std::make_shared<EApp>("main", v);
                                  }
;

formal:
  "var" ":" typ                   { $$ = arg_t($1, $3); }
;

formallist:
  formal                          {
                                    arglist_t v;
                                    v.push_back($1);
                                    $$ = v;
                                  }
| formallist "," formal            {
                                    arglist_t v = $1;
                                    v.push_back($3);
                                    $$ = v;
                                  }
;

decl:
  "let" "var" "(" formallist ")" ":" typ "=" exp ";;"
                                  {
                                    std::reverse($4.begin(), $4.end());
                                    function_t func = {
                                      .arglist = $4,
                                      .return_type = $7,
                                      .e = $9
                                    };
                                    global_functions.insert({$2, func});
                                  }
;

decllist:
  decl
| decllist decl
;

exp:
  exp_app                         { $$ = $1; }
;

exp_app:
  "var" expslist                  {
                                    std::reverse($2.begin(), $2.end());
                                    $$ = std::make_shared<EApp>($1, $2);
                                  }
| exp_ops                         { $$ = $1; }
;

expslist:
  exp_ops                         {
                                    std::vector<Shared_Exp> v;
                                    v.push_back($1);
                                    $$ = v;
                                  }
| expslist exp_ops                {
                                    $1.push_back($2);
                                    $$ = $1;
                                  }

exp_ops:
  exp_ops "+" exp_ops             { $$ = std::make_shared<EOperator>(TokenKind::Plus, $1, $3); }
| exp_ops "-" exp_ops             { $$ = std::make_shared<EOperator>(TokenKind::Subtract, $1, $3); }
| exp_ops "*" exp_ops             { $$ = std::make_shared<EOperator>(TokenKind::Multiply, $1, $3); }
| exp_ops "/" exp_ops             { $$ = std::make_shared<EOperator>(TokenKind::Divide, $1, $3); }
| exp_ops "<=" exp_ops            { $$ = std::make_shared<EComp>(TokenKind::Leq, $1, $3); }
| exp_ops "<" exp_ops             { $$ = std::make_shared<EComp>(TokenKind::Less, $1, $3); }
| exp_ops "==" exp_ops            { $$ = std::make_shared<EComp>(TokenKind::Equal, $1, $3); }
| exp_ops ">" exp_ops             { $$ = std::make_shared<EComp>(TokenKind::Greater, $1, $3); }
| exp_ops ">=" exp_ops            { $$ = std::make_shared<EComp>(TokenKind::Geq, $1, $3); }
| "(" exp_ops "," exp_ops ")"     { $$ = std::make_shared<EPair>($2, $4); }
| "fst" "(" exp_ops ")"           { $$ = std::make_shared<EFst>($3); }
| "snd" "(" exp_ops ")"           { $$ = std::make_shared<ESnd>($3); }
| "car" "(" exp_ops ")"           { $$ = std::make_shared<ECar>($3); }
| "cdr" "(" exp_ops ")"           { $$ = std::make_shared<ECdr>($3); }
| "empty" "(" exp_ops ")"         { $$ = std::make_shared<EEmpty>($3); }
| exp_ops "::" exp_ops            { $$ = std::make_shared<ECons>($1, $3); }
| "{" "}" ":" typ                 {
                                    std::vector<Shared_Exp> v;
                                    $$ = std::make_shared<EList>(v, $4);
                                  }
| "ref" "(" exp_ops ")"           { $$ = std::make_shared<ERef>($3); }
| "!" "(" exp_ops ")"             { $$ = std::make_shared<EDeref>($3); }
| exp_ops ":=" exp_ops            { $$ = std::make_shared<EAssign>($1, $3); }
| exp_ops ";" exp_ops             { $$ = std::make_shared<ESeq>($1, $3); }
// | "(" exp_ops ")" %prec "->"      { $$ = $2; }
| typ "var" "=" "{" exp_ops "}"   { $$ = std::make_shared<EDef>($2, $5, $1); }
| "struct" "{" struct_statement_list "}"
                                  {
                                    $$ = std::make_shared<EStruct>(global_struct_data, global_struct_type);
                                    global_struct_data.clear();
                                    global_struct_type.clear();
                                  }
| exp_ops  "." "var"              { $$ =  std::make_shared<EDot>($1, $3); }
| exp_base                        { $$ = $1; }
;

exp_base:
  "(" ")"                         { $$ = std::make_shared<EUnit>(); }
| "int"                           { $$ = std::make_shared<ELit>(true, $1, 0, false); }
| "double"                        { $$ = std::make_shared<ELit>(false, 0, $1, false); }
| "true"                          { $$ = std::make_shared<EBool>(true); }
| "false"                         { $$ = std::make_shared<EBool>(false); }
| "NaN"                           { $$ = std::make_shared<ELit>(false, 0, 0, true); }
| "var"                           { $$ = std::make_shared<EVar>($1); }
| "if" exp "then" exp "else" exp
                                  { $$ = std::make_shared<EIf>($2, $4, $6); }
| "let" "var" ":" typ  "=" exp "in" exp
                                  { $$ = std::make_shared<ELet>($2, $4, $6, $8); }
| "while" exp "do" exp "end"
                                  { $$ = std::make_shared<EWhile>($2, $4, $2); }
| "(" exp ")"                     { $$ = $2; }

struct_statement_list: struct_statement
| struct_statement_list struct_statement
;

struct_statement:
  typ "var" "=>" exp ","          {
                                        global_struct_data.insert({$2, $4});
                                        global_struct_type.insert({$2, $1});
                                      }
;

typ:
  "tint"                          { $$ = $1; }
| "tfloat"                        { $$ = $1; }
| "tbool"                         { $$ = $1; }
| "tunit"                         { $$ = $1; }
| "tstruct"                       { $$ = $1; }
| typ "->" typ                    { $$ = std::make_shared<TFunc>($1, $3); }
| typ "*" typ  %prec "->"         { $$ = std::make_shared<TPair>($1, $3); }
| "{" typ "}"                     { $$ = std::make_shared<TList>($2); }
| "<" typ ">"                     { $$ = std::make_shared<TRef>($2); }
| "(" typ ")"                     { $$ = $2; }

%%

// NOTE: Bison's error reporting simply forwards to the driver
void yy::parser::error(const yy::parser::location_type& l, const std::string &m) { driver.error(l, m); }
