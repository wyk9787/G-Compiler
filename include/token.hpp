#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace fexp {
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
class EDef;
class EStruct;
class EDot;
}

class Typ;
class TInt;
class TBool;
class TUnit;
class TFloat;
class TFunc;
class TPair;
class TList;
class TRef;
class TStruct;

/******************************************************************************
                               Alias for shared_ptr
*******************************************************************************/
typedef std::shared_ptr<fexp::Exp> Shared_Exp;
typedef std::shared_ptr<fexp::EOperator> Shared_EOperator;
typedef std::shared_ptr<fexp::EComp> Shared_EComp;
typedef std::shared_ptr<fexp::ELit> Shared_ELit;
typedef std::shared_ptr<fexp::EBool> Shared_EBool;
typedef std::shared_ptr<fexp::EVar> Shared_EVar;
typedef std::shared_ptr<fexp::EFunc> Shared_EFunc;
typedef std::shared_ptr<fexp::EIf> Shared_EIf;
typedef std::shared_ptr<fexp::ELet> Shared_ELet;
typedef std::shared_ptr<fexp::EApp> Shared_EApp;
typedef std::shared_ptr<fexp::EPair> Shared_EPair;
typedef std::shared_ptr<fexp::EFst> Shared_EFst;
typedef std::shared_ptr<fexp::ESnd> Shared_ESnd;
typedef std::shared_ptr<fexp::EList> Shared_EList;
typedef std::shared_ptr<fexp::ECons> Shared_ECons;
typedef std::shared_ptr<fexp::ECar> Shared_ECar;
typedef std::shared_ptr<fexp::ECdr> Shared_ECdr;
typedef std::shared_ptr<fexp::EEmpty> Shared_EEmpty;
typedef std::shared_ptr<fexp::ERef> Shared_ERef;
typedef std::shared_ptr<fexp::EDeref> Shared_EDeref;
typedef std::shared_ptr<fexp::EPtr> Shared_EPtr;
typedef std::shared_ptr<fexp::EAssign> Shared_EAssign;
typedef std::shared_ptr<fexp::ESeq> Shared_ESeq;
typedef std::shared_ptr<fexp::EWhile> Shared_EWhile;
typedef std::shared_ptr<fexp::EDef> Shared_EDef;
typedef std::shared_ptr<fexp::EStruct> Shared_EStruct;
typedef std::shared_ptr<fexp::EDot> Shared_EDot;

typedef std::shared_ptr<Typ> Shared_Typ;
typedef std::shared_ptr<TInt> Shared_TInt;
typedef std::shared_ptr<TFloat> Shared_TFloat;
typedef std::shared_ptr<TBool> Shared_TBool;
typedef std::shared_ptr<TUnit> Shared_TUnit;
typedef std::shared_ptr<TFunc> Shared_TFunc;
typedef std::shared_ptr<TPair> Shared_TPair;
typedef std::shared_ptr<TRef> Shared_TRef;
typedef std::shared_ptr<TStruct> Shared_TStruct;

typedef std::unordered_map<std::string, std::shared_ptr<fexp::Exp>> global_stack_t;
typedef std::unordered_map<std::string, std::shared_ptr<Typ>> context_t;
typedef std::unordered_map<size_t, std::shared_ptr<fexp::Exp>> global_heap_t;
typedef std::unordered_map<std::string, std::shared_ptr<fexp::Exp>> struct_data_t;
typedef std::unordered_map<std::string, std::shared_ptr<Typ>> struct_type_t;

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
