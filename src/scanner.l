%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "parser_driver.h"
# include "parser.yy.hpp"

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1
static yy::location loc;
%}

%option noyywrap nounput batch debug noinput


var         [a-zA-Z][a-zA-Z_0-9]*

int   [0-9]+
double [0-9]+"."[0-9]+
blank [ \t]

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}

%%

%{
  // Code run each time yylex is called.
  loc.step ();
%}

{blank}+    { loc.step (); }
[\n]+       { loc.lines (yyleng); loc.step (); }

"+"         { return yy::parser::make_PLUS(loc); }
"-"         { return yy::parser::make_SUBTRACT(loc); }
"*"         { return yy::parser::make_MULTIPLY(loc); }
"/"         { return yy::parser::make_DIVIDE(loc); }
"<="        { return yy::parser::make_LEQ(loc); }
"<"         { return yy::parser::make_LESS(loc); }
"=="        { return yy::parser::make_EQUAL(loc); }
">="        { return yy::parser::make_GEQ(loc); }
">"         { return yy::parser::make_GREATER(loc); }
"("         { return yy::parser::make_LPAREN(loc); }
")"         { return yy::parser::make_RPAREN(loc); }
"true"      { return yy::parser::make_TRUE(loc); }
"false"     { return yy::parser::make_FALSE(loc); }
"if"        { return yy::parser::make_IF(loc); }
"else"      { return yy::parser::make_ELSE(loc); }
"then"      { return yy::parser::make_THEN(loc); }
"NaN"       { return yy::parser::make_NAN(loc); }
"fun"       { return yy::parser::make_FUNC(loc); }
"->"        { return yy::parser::make_FUNC_BODY(loc); }
"=>"        { return yy::parser::make_ARROW(loc); }
"struct"    { return yy::parser::make_STRUCT(loc); }
"let"       { return yy::parser::make_LET(loc); }
"="         { return yy::parser::make_LET_ASSIGN(loc); }
"in"        { return yy::parser::make_IN(loc); }
"rec"       { return yy::parser::make_REC(loc); }
"[-]"       { struct_type_t temp;
  return yy::parser::make_TSTRUCT(std::make_shared<TStruct>(temp), loc); }
"int"       { return yy::parser::make_TINT(std::make_shared<TInt>(), loc); }
"float"     { return yy::parser::make_TFLOAT(std::make_shared<TFloat>(), loc); }
"bool"      { return yy::parser::make_TBOOL(std::make_shared<TBool>(), loc); }
"unit"      { return yy::parser::make_TUNIT(std::make_shared<TUnit>(), loc); }
":"         { return yy::parser::make_COL(loc); }
"["         { return yy::parser::make_LBRA(loc); }
"]"         { return yy::parser::make_RBRA(loc); }
"()"        { return yy::parser::make_UNIT(loc); }
","         { return yy::parser::make_COMMA(loc); }
"fst"       { return yy::parser::make_FST(loc); }
"snd"       { return yy::parser::make_SND(loc); }
"{"         { return yy::parser::make_LCURLY(loc); }
"}"         { return yy::parser::make_RCURLY(loc); }
"car"       { return yy::parser::make_CAR(loc); }
"cdr"       { return yy::parser::make_CDR(loc); }
"empty?"    { return yy::parser::make_EMPTY(loc); }
"::"        { return yy::parser::make_CONS(loc); }
"!"         { return yy::parser::make_DEREF(loc); }
"ref"       { return yy::parser::make_REF(loc); }
":="        { return yy::parser::make_ASSIGN(loc); }
";"         { return yy::parser::make_SEQ(loc); }
"while"     { return yy::parser::make_WHILE(loc); }
"do"        { return yy::parser::make_DO(loc); }
"end"       { return yy::parser::make_END(loc); }
"#"         { return yy::parser::make_POND(loc); }
"include"   { return yy::parser::make_INCLUDE(loc); }
"def"       { return yy::parser::make_DEF(loc); }
"."         { return yy::parser::make_DOT(loc); }

{var}       { return yy::parser::make_VAR(yytext, loc);}

{double} {
    errno = 0;
    double n = strtod (yytext, NULL);

    return yy::parser::make_DOUBLE(n, loc);
}

{int} {
    errno = 0;
    long n = strtol (yytext, NULL, 10);
    if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
        driver.error (loc, "integer is out of range");
    }
    return yy::parser::make_INT(n, loc);
}

.          { driver.error (loc, "invalid character"); }
<<EOF>>    { return yy::parser::make_EOF(loc); }
%%

void parser_driver::scan_begin () {
    yy_flex_debug = trace_scanning;
    if (file.empty () || file == "-") {
        yyin = stdin;
    } else if (!(yyin = fopen (file.c_str (), "r"))) {
        error (loc, "cannot open " + file + ": " + strerror(errno));
        exit (EXIT_FAILURE);
    }
}

void parser_driver::scan_end () {
    fclose (yyin);
}
