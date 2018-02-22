#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <vector>

const std::vector<std::string> enum_string = {
    "(", ")", "+", "-",  "/", "*", " ",
    "true",   "false",  "ifs",   "<=", "NaN",    " "};

typedef enum {
  LParen = 0,
  RParen = 1,
  Plus = 2,
  Subtract = 3,
  Divide = 4,
  Multiply = 5,
  Num_Int = 6,
  True = 7,
  False = 8,
  If = 9,
  Less_Than = 10,
  Lit_NaN = 11,
  Num_Float = 12,
  Eol = 13
} TokenKind;

typedef struct {
  TokenKind id;
  int int_data;
  double float_data;
  bool bool_data;
} Token;

typedef enum { Int, Float, Bool, NaN } ResultKind;

typedef struct {
  ResultKind id;
  int int_data;
  double float_data;
  bool bool_data;
} Result;

#endif
