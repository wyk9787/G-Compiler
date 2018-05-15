#ifndef TOKEN_HPP
#define TOKEN_HPP

// Empty strings are place holders for int, float, bool, var and fun
const std::vector<std::string> enum_string = {"(", ")",  "+",   "-",  "/", "*",
                                              " ", " ",  "if",  "<=", "<", "==",
                                              ">", ">=", "NaN", " ",  " ", " "};

// bool print_step;

typedef enum {
  LParen = 0,
  RParen,
  Plus,
  Subtract,
  Divide,
  Multiply,
  Int,
  Bool,
  If,
  Leq,
  Less,
  Equal,
  Greater,
  Geq,
  NaN,
  Float,
  Var,
  Fun
} TokenKind;

#endif
