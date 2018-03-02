#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <vector>
#include <unordered_map>

class Exp;
class EOperator;
class EComp;
class ELit;
class EBool;
class EVar;
class EFunc;
class EIf;
class ELet;
class EApp;

class Typ;
class TInt;
class TBool;
class TFloat;
class TFunc;

/******************************************************************************
                               Alias for shared_ptr
*******************************************************************************/
typedef std::shared_ptr<Exp> Shared_Exp;
typedef std::shared_ptr<EOperator> Shared_EOperator;
typedef std::shared_ptr<EComp> Shared_EComp;
typedef std::shared_ptr<ELit> Shared_ELit;
typedef std::shared_ptr<EBool> Shared_EBool;
typedef std::shared_ptr<EVar> Shared_EVar;
typedef std::shared_ptr<EFunc> Shared_EFunc;
typedef std::shared_ptr<EIf> Shared_EIf;
typedef std::shared_ptr<ELet> Shared_ELet;
typedef std::shared_ptr<EApp> Shared_EApp;

typedef std::shared_ptr<Typ> Shared_Typ;
typedef std::shared_ptr<TInt> Shared_TInt;
typedef std::shared_ptr<TFloat> Shared_TFloat;
typedef std::shared_ptr<TBool> Shared_TBool;
typedef std::shared_ptr<TFunc> Shared_TFunc;
typedef std::unordered_map<std::string, std::shared_ptr<Typ>> context_t;

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
