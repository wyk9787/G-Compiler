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
class EPair;
class EFst;
class ESnd;
class EList;
class ECons;
class ECar;
class ECdr;
class EEmpty;
class ERef;
class EDeref;
class EPtr;
class EAssign;
class ESeq;
class EWhile;

class Typ;
class TInt;
class TBool;
class TUnit;
class TFloat;
class TFunc;
class TPair;
class TList;
class TRef;

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
typedef std::shared_ptr<EPair> Shared_EPair;
typedef std::shared_ptr<EFst> Shared_EFst;
typedef std::shared_ptr<ESnd> Shared_ESnd;
typedef std::shared_ptr<EList> Shared_EList;
typedef std::shared_ptr<ECons> Shared_ECons;
typedef std::shared_ptr<ECar> Shared_ECar;
typedef std::shared_ptr<ECdr> Shared_ECdr;
typedef std::shared_ptr<EEmpty> Shared_EEmpty;
typedef std::shared_ptr<ERef> Shared_ERef;
typedef std::shared_ptr<EDeref> Shared_EDeref;
typedef std::shared_ptr<EPtr> Shared_EPtr;
typedef std::shared_ptr<EAssign> Shared_EAssign;
typedef std::shared_ptr<ESeq> Shared_ESeq;
typedef std::shared_ptr<EWhile> Shared_EWhile;

typedef std::shared_ptr<Typ> Shared_Typ;
typedef std::shared_ptr<TInt> Shared_TInt;
typedef std::shared_ptr<TFloat> Shared_TFloat;
typedef std::shared_ptr<TBool> Shared_TBool;
typedef std::shared_ptr<TUnit> Shared_TUnit;
typedef std::shared_ptr<TFunc> Shared_TFunc;
typedef std::shared_ptr<TPair> Shared_TPair;
typedef std::shared_ptr<TRef> Shared_TRef;

typedef std::unordered_map<std::string, std::shared_ptr<Typ>> context_t;
typedef std::unordered_map<size_t, std::shared_ptr<Exp>> env_t;

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
