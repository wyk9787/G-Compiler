#ifndef GLOBAL_HPP
#define GLOBAL_HPP
#include <string>
#include <token.hpp>
#include <unordered_map>
#include <vector>

namespace fexp {
class Exp;
class EOperator;
class EComp;
class ELit;
class EBool;
class EVar;
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
}

namespace cexp {
class Exp;
class EOperator;
class ELit;
class EBool;
class EVar;
class EIf;
class EApp;
class EWhile;
}

namespace ftyp {
class Typ;
class TInt;
class TBool;
class TUnit;
class TPair;
class TList;
class TRef;
}

namespace ctyp {
class Typ;
class TInt;
class TBool;
}

class Stmt;
class SDecl;
class SWhile;
class SIf;
class SRet;
class SPrint;

/******************************************************************************
                               Alias for shared_ptr
*******************************************************************************/
namespace fexp {

using namespace fexp;

typedef std::shared_ptr<Exp> Shared_Exp;
typedef std::shared_ptr<EOperator> Shared_EOperator;
typedef std::shared_ptr<EComp> Shared_EComp;
typedef std::shared_ptr<ELit> Shared_ELit;
typedef std::shared_ptr<EBool> Shared_EBool;
typedef std::shared_ptr<EVar> Shared_EVar;
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
}

namespace cexp {

using namespace cexp;

typedef std::shared_ptr<Exp> Shared_Exp;
typedef std::shared_ptr<EOperator> Shared_EOperator;
typedef std::shared_ptr<ELit> Shared_ELit;
typedef std::shared_ptr<EBool> Shared_EBool;
typedef std::shared_ptr<EVar> Shared_EVar;
typedef std::shared_ptr<EIf> Shared_EIf;
typedef std::shared_ptr<EApp> Shared_EApp;
typedef std::shared_ptr<EWhile> Shared_EWhile;
}

namespace ftyp {

using namespace ftyp;

typedef std::shared_ptr<Typ> Shared_Typ;
typedef std::shared_ptr<TInt> Shared_TInt;
typedef std::shared_ptr<TBool> Shared_TBool;
typedef std::shared_ptr<TUnit> Shared_TUnit;
typedef std::shared_ptr<TPair> Shared_TPair;
typedef std::shared_ptr<TRef> Shared_TRef;
}

namespace ctyp {

using namespace ctyp;

typedef std::shared_ptr<Typ> Shared_Typ;
typedef std::shared_ptr<TInt> Shared_TInt;
typedef std::shared_ptr<TBool> Shared_TBool;
}

typedef std::shared_ptr<Stmt> Shared_Stmt;
typedef std::shared_ptr<SDecl> Shared_SDecl;
typedef std::shared_ptr<SWhile> Shared_SWhile;
typedef std::shared_ptr<SIf> Shared_SIf;
typedef std::shared_ptr<SRet> Shared_SRet;
typedef std::shared_ptr<SPrint> Shared_SPrint;
/******************************************************************************

*******************************************************************************/

typedef std::unordered_map<std::string, ftyp::Shared_Typ> context_t;
typedef std::unordered_map<size_t, fexp::Shared_Exp> global_heap_t;

// Functions for the functional language
typedef std::pair<std::string, ftyp::Shared_Typ> arg_t;
typedef std::vector<arg_t> arglist_t;
typedef struct _function {
  std::string name;
  arglist_t arglist;
  ftyp::Shared_Typ return_type;
  fexp::Shared_Exp e;
} function_t;
typedef std::unordered_map<std::string, function_t> global_function_t;

// Functions for C
typedef std::pair<std::string, ctyp::Shared_Typ> c_arg_t;
typedef std::vector<c_arg_t> c_arglist_t;
typedef struct _c_function {
  std::string name;
  c_arglist_t arglist;
  ctyp::Shared_Typ return_type;
  std::vector<Shared_Stmt> stmt_list;
} c_function_t;
typedef std::unordered_map<std::string, c_function_t> c_global_function_t;

// Globals
extern global_heap_t heap;
extern global_function_t global_functions;

#endif
