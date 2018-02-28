#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <vector>

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

// struct Func {
//   std::string parameter;
//   std::shared_ptr<Exp> e;
//   bool is_recursive;
//   std::string id;
//
//   // Func(std::string _parameter, std::shared_ptr<Exp> _e, bool _is_recursive,
//   //      std::string _id)
//   //     : parameter(_parameter), e(_e), is_recursive(_is_recursive), id(_id) {};
// };
//
// typedef struct {
//   TokenKind id;
//   int int_data;
//   double float_data;
//   bool bool_data;
//   std::string var_data;
//   Func func_data;
// } Token;

// typedef enum { Int, Float, Bool, NaN, Var } ResultKind;
//
// typedef struct {
//   ResultKind id;
//   int int_data;
//   double float_data;
//   bool bool_data;
//   std::string var_data;
// } Result;

#endif
