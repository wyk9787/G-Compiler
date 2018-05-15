#include "expression.hpp"
#include "c_expression.hpp"
#include <iostream>
#include <stdlib.h>

global_heap_t heap;
global_function_t global_functions;

using namespace fexp;
using namespace ftyp;

/****** Helper Functions for Converting to C *****/

std::string fresh_name() {
  static size_t count = 0;
  return "_g" + std::to_string(count++) + "comp";
}

std::tuple<std::string id, std::vector<Shared_Stmt>, Shared_Stmt> factor_subexp(Shared_Exp e) {
  std::string name = fresh_name();
  auto conv = e->convert();
  return std::make_tuple(name, conv.second,
                         std::make_shared<SDecl>(name, std::make_shared<ctyp::Tint>(),
                                                 conv.first));
}

std::pair<std::vector<Shared_Exp>, std::vector<Shared_Stmt>> factor_subexps(std::vector<Shared_Exp> es, std::vector<cexp::Shared_Exp> exp_so_far, std::vector<Shared_Stmt> stmt_so_far) {
  if(es.size() == 0) {
    return {exp_so_far, stmt_so_far};
  } else {
    auto subexp = factor_subexp(es[0]);
    es.erase(subexp);

    std::vector<cexp::Shared_Exp> new_exp_so_far(exp_so_far);
    new_exp_so_far.push_back(std::make_shared<cexp::EVar>(std::get<0>(subexp)));

    std::vector<cexp::Shared_Stmt> new_stmt_so_far(stmt_so_far);
    auto new_ss = std::get<1>(subexp);
    new_stmt_so_far.insert(new_stmt_so_far.end(), new_ss.begin(), new_ss.end());
    new_stmt_so_far.push_back(std::get<2>(subexp));
    return factor_subexps(es, new_exp_so_far, new_stmt_so_far);
  }
}

/*************************************************/

std::shared_ptr<Exp> fexp::evaluate(std::shared_ptr<Exp> exp, bool print_step) {
  while (!exp->is_value()) {
    if (print_step) {
      std::cout << exp->string_of_exp() << std::endl;
    }
    exp = exp->step();
  }
  return exp;
}

/******************************************************************************
                        EOperator Implementaion
*******************************************************************************/

EOperator::EOperator(TokenKind _id, Shared_Exp _e1, Shared_Exp _e2)
    : id(_id), e1(_e1), e2(_e2) {}

// Private method
Shared_Exp EOperator::evaluate_num(Shared_Exp e1_lit, Shared_Exp e2_lit,
                                   bool _is_int) {
  auto e1_data = e1->is_int() ? e1->get_int() : e1->get_float();
  auto e2_data = e2->is_int() ? e2->get_int() : e2->get_float();
  bool is_NaN = false;
  auto temp_data = e1_data + e2_data;
  switch (id) {
  case Plus:
    temp_data = e1_data + e2_data;
    break;
  case Subtract:
    temp_data = e1_data - e2_data;
    break;
  case Multiply:
    temp_data = e1_data * e2_data;
    break;
  case Divide: {
    if (e2_data != 0) {
      temp_data = e1_data / e2_data;
    } else if (e1_data == 0) { // e1_data = 0 and e2_data = 0
      is_NaN = true;
    } else {
      std::cerr << "Fatal: Division by 0" << std::endl;
      exit(1);
    }
    break;
  }
  default:
    std::cout << e1->string_of_exp() << std::endl;
    std::cout << e2->string_of_exp() << std::endl;
    std::cout << id << std::endl;
    std::cerr << "Expecting arithmetic operation" << std::endl;
    exit(1);
  }
  if (_is_int) {
    return std::make_shared<ELit>(_is_int, temp_data, 0, is_NaN);
  } else {
    return std::make_shared<ELit>(_is_int, 0, temp_data, is_NaN);
  }
}

Shared_Exp EOperator::step() {
  if (!e1->is_value()) {
    return std::make_shared<EOperator>(id, e1->step(), e2);
  } else if (!e2->is_value()) {
    return std::make_shared<EOperator>(id, e1, e2->step());
  } else {
    if (e1->is_NaN() || e2->is_NaN()) {
      return std::make_shared<ELit>(false, 0, 0, true);
    }
    if (!e1->is_int() && !e2->is_int() && !e1->is_float() && !e2->is_float()) {
      std::cerr << "Expecting a literal (integer or value)" << std::endl;
      exit(1);
    }
    bool is_int = e1->is_int() && e2->is_int();
    return evaluate_num(e1, e2, is_int);
  }
}

Shared_Exp EOperator::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EOperator>(id, e1->substitute(var, e),
                                     e2->substitute(var, e));
}

std::string EOperator::string_of_exp() {
  return "(" + e1->string_of_exp() + " " + enum_string[id] + " " +
         e2->string_of_exp() + ")";
}

Shared_Typ EOperator::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  Shared_Typ t2 = e2->typecheck(context);
  if (dynamic_cast<TInt *>(t1.get()) == nullptr &&
      dynamic_cast<TFloat *>(t1.get()) == nullptr) {
    type_error(string_of_exp(), "Int or Float", t1->get_type());
  } else if (dynamic_cast<TInt *>(t2.get()) == nullptr &&
             dynamic_cast<TFloat *>(t2.get()) == nullptr) {
    type_error(string_of_exp(), "Int or Float", t2->get_type());
  } else if (*t1.get() != *t2.get()) {
    type_error(string_of_exp(), t1->get_type(), t2->get_type());
  } else {
    return t1;
  }

  return nullptr;
}

std::pair<cexp::Shared_Exp, std::vector<Shared_Stmt>> EOperator::convert() {
  // TODO: Can we save a local variable here?
  auto subexp1 = factor_subexp(e1);
  auto subexp2 = factor_subexp(e2);
  std::vector<Shared_Stmt> v(std::get<1>(subexp1));
  auto v2 = std::get<1>(subexp2);
  v.insert(v.end(), v2.begin(), v2.end());
  v.push_back(std::get<2>(subexp1));
  v.push_back(std::get<2>(subexp2));
  return {std::make_shared<cexp::EOperator>(id, std::make_share<EVar>(std::get<0>(subexp1)), std::make_share<EVar>(std::get<0>(subexp2))),v};
}

/******************************************************************************
                        EComp Implementaion
*******************************************************************************/
EComp::EComp(TokenKind _id, Shared_Exp _e1, Shared_Exp _e2)
    : id(_id), e1(_e1), e2(_e2) {}

// Private method
Shared_Exp EComp::evaluate_bool(Shared_Exp e1, Shared_Exp e2) {
  auto e1_data = e1->is_int() ? e1->get_int() : e1->get_float();
  auto e2_data = e2->is_int() ? e2->get_int() : e2->get_float();

  bool result;
  switch (id) {
  case Leq:
    result = e1_data <= e2_data;
    break;
  case Less:
    result = e1_data < e2_data;
    break;
  case Equal:
    result = e1_data == e2_data;
    break;
  case Greater:
    result = e1_data > e2_data;
    break;
  case Geq:
    result = e1_data >= e2_data;
    break;
  default:
    std::cerr << "Expecting literals (integer or float)" << std::endl;
    exit(1);
  }

  return std::make_shared<EBool>(result);
}

Shared_Exp EComp::step() {
  if (!e1->is_value()) {
    return std::make_shared<EComp>(id, e1->step(), e2);
  } else if (!e2->is_value()) {
    return std::make_shared<EComp>(id, e1, e2->step());
  } else {
    if (e1->is_NaN() || e2->is_NaN()) {
      return std::make_shared<ELit>(false, 0, 0, true);
    }
    if (!e1->is_int() && !e2->is_int() && !e1->is_float() && !e2->is_float()) {
      std::cerr << "Expecting a literal (integer or value)" << std::endl;
      exit(1);
    }
    return evaluate_bool(e1, e2);
  }
}

Shared_Exp EComp::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EComp>(id, e1->substitute(var, e),
                                 e2->substitute(var, e));
}

std::string EComp::string_of_exp() {
  return "(" + e1->string_of_exp() + " " + enum_string[id] + " " +
         e2->string_of_exp() + ")";
}

Shared_Typ EComp::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  Shared_Typ t2 = e2->typecheck(context);
  if (dynamic_cast<TInt *>(t1.get()) == nullptr &&
      dynamic_cast<TFloat *>(t1.get()) == nullptr) {
    type_error(string_of_exp(), "Int or Float", t1->get_type());
  } else if (dynamic_cast<TInt *>(t2.get()) == nullptr &&
             dynamic_cast<TFloat *>(t2.get()) == nullptr) {
    type_error(string_of_exp(), "Int or Float", t2->get_type());
  } else if (*t1.get() != *t2.get()) {
    type_error(string_of_exp(), t1->get_type(), t2->get_type());
  } else {
    return std::make_shared<TBool>();
  }

  return nullptr;
}

// This is exactly the same as the version in EOperator because I only have cexp::EOperator
std::pair<cexp::Shared_Exp, std::vector<Shared_Stmt>> EComp::convert() {
  // TODO: Can we save a local variable here?
  auto subexp1 = factor_subexp(e1);
  auto subexp2 = factor_subexp(e2);
  std::vector<Shared_Stmt> v(std::get<1>(subexp1));
  auto v2 = std::get<1>(subexp2);
  v.insert(v.end(), v2.begin(), v2.end());
  v.push_back(std::get<2>(subexp1));
  v.push_back(std::get<2>(subexp2));
  return {std::make_shared<cexp::EOperator>(id, std::make_share<EVar>(std::get<0>(subexp1)), std::make_share<EVar>(std::get<0>(subexp2))),v};
}

/******************************************************************************
                        ELit Implementaion
*******************************************************************************/

ELit::ELit(int _data) : data(_data){};

Shared_Exp ELit::step() { return std::make_shared<ELit>(data); }

Shared_Exp ELit::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<ELit>(data);
}

std::string ELit::string_of_exp() { return std::to_string(data); }

Shared_Typ ELit::typecheck(context_t context) {
  return std::make_shared<TInt>();
}

bool ELit::is_value() { return true; }

bool ELit::is_Lit() { return true; }

int ELit::get_lit() { return data; }

std::pair<cexp::Shared_Exp, std::vector<Shared_Stmt>> ELit::convert() {
  std::vector<Shared_Stmt> v;
  return {std::make_shared<cexp::EInt>(data), v};
}

/******************************************************************************
                        EBool Implementaion
*******************************************************************************/

EBool::EBool(bool _data) : data(_data){};

Shared_Exp EBool::step() { return std::make_shared<EBool>(data); }

Shared_Exp EBool::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EBool>(data);
}

std::string EBool::string_of_exp() { return data ? "true" : "false"; }

Shared_Typ EBool::typecheck(context_t context) {
  return std::make_shared<TBool>();
}

std::pair<cexp::Shared_Exp, std::vector<Shared_Stmt>> EBool::convert() {
  std::vector<Shared_Stmt> v;
  return {std::make_shared<cexp::EBool>(data), v};
}

bool EBool::is_value() { return true; }

bool EBool::is_bool() { return true; }

bool EBool::get_bool() { return data; }

/******************************************************************************
                        EVar Implementaion
*******************************************************************************/

EVar::EVar(std::string _data) : data(_data){};

Shared_Exp EVar::step() { return std::make_shared<EVar>(data); }

Shared_Exp EVar::substitute(std::string var, Shared_Exp e) {
  if (var == data) {
    return e;
  } else {
    return std::make_shared<EVar>(data);
  }
}

std::string EVar::string_of_exp() { return data; }

Shared_Typ EVar::typecheck(context_t context) {
  if (context.find(data) != context.end()) {
    return context[data];
  } else {
    std::cerr << "Requires a type for " << data << std::endl;
    exit(1);
  }
}

std::pair<cexp::Shared_Exp, std::vector<Shared_Stmt>> EVar::convert() {
  std::vector<Shared_Stmt> v;
  return {std::make_shared<cexp::EVar>(data), v};
}

bool EVar::is_value() { return true; }

bool EVar::is_var() { return true; }

std::string EVar::get_var() { return data; }

/******************************************************************************
                               EUnit Header
*******************************************************************************/

EUnit::EUnit(){};

Shared_Exp EUnit::step() { return std::make_shared<EUnit>(); }

Shared_Exp EUnit::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EUnit>();
}

std::string EUnit::string_of_exp() { return "()"; }

Shared_Typ EUnit::typecheck(context_t context) {
  return std::make_shared<TUnit>();
}

std::pair<cexp::Shared_Exp, std::vector<Shared_Stmt>> EUnit::convert() {
  std::vector<Shared_Stmt> v;
  return {std::make_shared<cexp::EInt>(0), v};
}

bool EUnit::is_value() { return true; }

bool EUnit::is_unit() { return true; }
/******************************************************************************
                        EIf Implementaion
*******************************************************************************/

EIf::EIf(Shared_Exp _e1, Shared_Exp _e2, Shared_Exp _e3)
    : e1(_e1), e2(_e2), e3(_e3) {}

Shared_Exp EIf::step() {
  if (!e1->is_value()) {
    return std::make_shared<EIf>(e1->step(), e2, e3);
  }
  if (e1->is_bool()) {
    if (e1->get_bool()) {
      return e2;
    } else {
      return e3;
    }
  } else {
    std::cerr << "Expecting a boolean!" << std::endl;
    exit(1);
  }
}

Shared_Exp EIf::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EIf>(e1->substitute(var, e), e2->substitute(var, e),
                               e3->substitute(var, e));
}

Shared_Typ EIf::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  Shared_Typ t2 = e2->typecheck(context);
  Shared_Typ t3 = e3->typecheck(context);
  if (dynamic_cast<TBool *>(t1.get()) == nullptr) {
    type_error(string_of_exp(), "Boolean", t1->get_type());
  } else if (*t2.get() != *t3.get()) {
    type_error(string_of_exp(), t2->get_type(), t3->get_type());
  } else {
    return t2;
  }
  return nullptr;
}

std::string EIf::string_of_exp() {
  return "if (" + e1->string_of_exp() + ") {" + e2->string_of_exp() +
         "} else {" + e3->string_of_exp() + "}";
}

std::pair<cexp::Shared_Exp, std::vector<Shared_Stmt>> EIf::convert() {
  auto subexp1 = factor_subexp(e1);
  auto subexp2 = factor_subexp(e2);
  auto subexp3 = factor_subexp(e3);
  std::string ret = fresh_name();

  std::vector<Shared_Stmt> ss2(std::get<1>(subexp2));
  v.push_back(std::get<2>(subexp2));
  v.push_back(std::make_shared<SDecl>(ret, std::make_shared<ctyp::TInt>(), std::make_shared<cexp::Var>(std::get<0>(subexp3))));

  std::vector<Shared_Stmt> ss3(std::get<1>(subexp3));
  v.push_back(std::get<2>(subexp3));
  v.push_back(std::make_shared<SDecl>(ret, std::make_shared<ctyp::TInt>(), std::make_shared<cexp::Var>(std::get<0>(subexp3))));

  std::vector<Shared_Stmt> res(std::get<0>(subexp1));
  res.push_back(std::make_shared<SIf>(std::make_shared<cexp::EVar>(std::get<0>(subexp1)), ss2, ss3));
  return {std::make_shared<cexp::EVar>(ret), rest};
}

/******************************************************************************
                        ELet Implementaion
*******************************************************************************/

ELet::ELet(std::string _var, Shared_Typ _t, Shared_Exp _e1, Shared_Exp _e2)
    : var(_var), t(_t), e1(_e1), e2(_e2) {}

Shared_Exp ELet::step() {
  if (!e1->is_value()) {
    return std::make_shared<ELet>(var, t, e1->step(), e2);
  } else {
    return e2->substitute(var, e1);
  }
}

Shared_Exp ELet::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<ELet>(this->var, t, e1->substitute(var, e),
                                e2->substitute(var, e));
}

std::string ELet::string_of_exp() {
  return "(let [" + var + " : " + t->get_type() + "]" + " = " +
         e1->string_of_exp() + " in " + e2->string_of_exp() + ")";
}

Shared_Typ ELet::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  if (context.find(var) == context.end()) {
    context.insert({var, t});
  } else {
    context[var] = t;
  }

  Shared_Typ t2 = e2->typecheck(context);
  if (*t1.get() != *t.get()) {
    type_error(string_of_exp(), t->get_type(), t1->get_type());
  } else {
    return t2;
  }
  return nullptr;
}

std::pair<cexp::Shared_Exp, std::vector<Shared_Stmt>> ELet::convert() {
  auto convert_exp = e1->convert();
  auto subexp1 = factor_subexp(e2);
  std::vector<Shared_Stmt> v(std::get<1>(convert_exp));
  v.push_back(std::make_shared<SDecl>(var, std::make_shared<ctyp::TInt>(), std::get<0>(convert_exp)));
  auto v2 = std::get<1>(subexp1);
  v.push_back(v.end(), v2.begin(), v2.end());
  v.push_back(std::get<2>(subexp1));
  return {std::make_shared<cexp::EVar>(std::get<0>(subexp1)), v};
}

/******************************************************************************
                        EApp Implementaion
*******************************************************************************/

EApp::EApp(std::string _id, std::vector<Shared_Exp> _v) : id(_id), v(_v) {}

Shared_Exp EApp::step() {
  for (int i = 0; i < v.size(); i++) {
    if (!v[i]->is_value()) {
      v[i] = v[i]->step();
      return std::make_shared<EApp>(id, v);
    }
  }

  function_t func = global_functions[id];
  arglist_t arglist = func.arglist;
  Shared_Exp ret = func.e;
  for (int i = 0; i < v.size(); i++) {
    ret = ret->substitute(arglist[i].first, v[i]);
  }

  return ret;
}

Shared_Exp EApp::substitute(std::string var, Shared_Exp _e) {
  std::vector<Shared_Exp> new_v(v);
  for (int i = 0; i < v.size(); i++) {
    new_v[i] = new_v[i]->substitute(var, _e);
  }
  return std::make_shared<EApp>(id, new_v);
}

std::string EApp::string_of_exp() {
  std::string ret = id + "(";
  for (int i = 0; i < v.size(); i++) {
    ret += v[i]->string_of_exp();
    if (i != v.size() - 1) {
      ret += ", ";
    }
  }
  ret += ")";
  return ret;
}

Shared_Typ EApp::typecheck(context_t context) {
  function_t func;

  // Find the function, if not, throw an error
  if (global_functions.find(id) != global_functions.end()) {
    func = global_functions[id];
  } else {
    std::cerr << "There is no function named " << id << std::endl;
    exit(1);
  }

  // Check for if the number of arguments match or not
  arglist_t arglist = func.arglist;
  if (arglist.size() != v.size()) {
    std::cerr << "Number of argument mismatches: Expect " << arglist.size()
              << " arguments, given " << v.size() << std::endl;
    exit(1);
  }

  // Typecheck each arguments
  for (int i = 0; i < arglist.size(); i++) {
    Shared_Typ t = v[i]->typecheck(context);
    if (*t.get() != *arglist[i].second.get()) {
      type_error(string_of_exp(), arglist[i].second->get_type(), t->get_type());
    }
  }

  return func.return_type;
}

std::pair<cexp::Shared_Exp, std::vector<Shared_Stmt>> EApp::convert() {
  std::vector<cexp::Shared_Exp> exp_so_far;
  std::vector<Shared_Stmt> stmt_so_far;
  auto subexps = factor_subexps(v, exp_so_far, stmt_so_far);
  return {std::make_shared<cexp::EApp>(id, std::get<0>(subexps)), std::get<1>(subexps)};
}

/******************************************************************************
                               EPair Implementaion
*******************************************************************************/
EPair::EPair(Shared_Exp _e1, Shared_Exp _e2) : e1(_e1), e2(_e2) {}

Shared_Exp EPair::step() {
  if (!e1->is_value()) {
    return std::make_shared<EPair>(e1->step(), e2);
  } else if (!e2->is_value()) {
    return std::make_shared<EPair>(e1, e2->step());
  }

  return std::make_shared<EPair>(e1, e2);
}

Shared_Exp EPair::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EPair>(e1->substitute(var, e),
                                 e2->substitute(var, e));
}

std::string EPair::string_of_exp() {
  return "(" + e1->string_of_exp() + ", " + e2->string_of_exp() + ")";
}

Shared_Typ EPair::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  Shared_Typ t2 = e2->typecheck(context);
  return std::make_shared<TPair>(t1, t2);
}

bool EPair::is_value() { return e1->is_value() && e2->is_value(); }

bool EPair::is_pair() { return e1->is_value() && e2->is_value(); }

Shared_EPair EPair::get_pair() { return std::make_shared<EPair>(e1, e2); }

Shared_Exp EPair::get_first() { return e1; }

Shared_Exp EPair::get_second() { return e2; }

/******************************************************************************
                               EFst Implementaion
*******************************************************************************/

EFst::EFst(Shared_Exp _e) : e(_e){};

Shared_Exp EFst::step() {
  if (!e->is_value()) {
    return std::make_shared<EFst>(e->step());
  }
  Shared_EPair pair = e->get_pair();
  return pair->get_first();
}

Shared_Exp EFst::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EFst>(this->e->substitute(var, e));
}

std::string EFst::string_of_exp() { return "fst (" + e->string_of_exp() + ")"; }

Shared_Typ EFst::typecheck(context_t context) {
  Shared_Typ t = e->typecheck(context);
  if (dynamic_cast<TPair *>(t.get()) == nullptr) {
    type_error(string_of_exp(), "Pair", t->get_type());
  } else {
    return t->get_first_subtype();
  }
  return nullptr;
}

/******************************************************************************
                               ESnd Implementaion
*******************************************************************************/

ESnd::ESnd(Shared_Exp _e) : e(_e) {}

Shared_Exp ESnd::step() {
  if (!e->is_value()) {
    return std::make_shared<ESnd>(e->step());
  }
  Shared_EPair pair = e->get_pair();
  return pair->get_second();
}

Shared_Exp ESnd::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<ESnd>(this->e->substitute(var, e));
}

std::string ESnd::string_of_exp() { return "snd (" + e->string_of_exp() + ")"; }

Shared_Typ ESnd::typecheck(context_t context) {
  Shared_Typ t = e->typecheck(context);
  if (dynamic_cast<TPair *>(t.get()) == nullptr) {
    type_error(string_of_exp(), "Pair", t->get_type());
  } else {
    return t->get_second_subtype();
  }
  return nullptr;
}

/******************************************************************************
                               EList Implementaion
*******************************************************************************/

EList::EList(std::vector<Shared_Exp> _e_list, Shared_Typ _t)
    : e_list(_e_list), t(_t) {}

Shared_Exp EList::step() { return std::make_shared<EList>(e_list, t); }

Shared_Exp EList::substitute(std::string var, Shared_Exp e) {
  std::vector<Shared_Exp> new_e_list;
  for (size_t i = 0; i < e_list.size(); i++) {
    new_e_list.push_back(e_list[i]->substitute(var, e));
  }
  return std::make_shared<EList>(new_e_list, t);
}

std::string EList::string_of_exp() {
  std::string res = "{";
  for (size_t i = 0; i < e_list.size(); i++) {
    res += e_list[i]->string_of_exp();
    if (i != e_list.size() - 1) {
      res += ", ";
    }
  }
  res += "}:" + t->get_type();
  return res;
}

Shared_Typ EList::typecheck(context_t context) {
  return std::make_shared<TList>(t);
}

bool EList::is_value() { return true; }

bool EList::is_list() { return true; }

Shared_EList EList::get_list() { return std::make_shared<EList>(e_list, t); }

Shared_Typ EList::get_t() { return t; }

std::vector<Shared_Exp> EList::get_e_list() { return e_list; }

/******************************************************************************
                               ECons Implementaion
*******************************************************************************/

ECons::ECons(Shared_Exp _e1, Shared_Exp _e2) : e1(_e1), e2(_e2) {}

Shared_Exp ECons::step() {
  if (!e1->is_value()) {
    return std::make_shared<ECons>(e1->step(), e2);
  } else if (!e2->is_value()) {
    return std::make_shared<ECons>(e1, e2->step());
  } else {
    Shared_EList l = e2->get_list();
    std::vector<Shared_Exp> e_list = l->get_e_list();
    e_list.insert(e_list.begin(), e1);
    Shared_Typ t = l->get_t();
    return std::make_shared<EList>(e_list, t);
  }
}

Shared_Exp ECons::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<ECons>(e1->substitute(var, e),
                                 e2->substitute(var, e));
}

std::string ECons::string_of_exp() {
  return e1->string_of_exp() + "::" + e2->string_of_exp();
}

Shared_Typ ECons::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  Shared_Typ t2 = e2->typecheck(context);
  if (dynamic_cast<TList *>(t2.get()) == nullptr) {
    type_error(string_of_exp(), "{t}", t2->get_type());
  }
  Shared_Typ t2_1 = t2->get_first_subtype();
  if (*t1.get() != *t2_1.get()) {
    type_error(string_of_exp(), t2_1->get_type(), t1->get_type());
  } else {
    return std::make_shared<TList>(t1);
  }
  return nullptr;
}

/******************************************************************************
                               ECar Implementaion
*******************************************************************************/

ECar::ECar(Shared_Exp _e) : e(_e) {}

Shared_Exp ECar::step() {
  if (!e->is_value()) {
    return std::make_shared<ECar>(e->step());
  } else {
    return e->get_list()->get_e_list()[0];
  }
}

Shared_Exp ECar::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<ECar>(this->e->substitute(var, e));
}

std::string ECar::string_of_exp() { return "car (" + e->string_of_exp() + ")"; }

Shared_Typ ECar::typecheck(context_t context) {
  Shared_Typ t = e->typecheck(context);
  if (dynamic_cast<TList *>(t.get()) == nullptr) {
    type_error(string_of_exp(), "{t}", t->get_type());
  } else {
    return t->get_first_subtype();
  }

  return nullptr;
}

/******************************************************************************
                               ECdr Implementaion
*******************************************************************************/

ECdr::ECdr(Shared_Exp _e) : e(_e) {}

Shared_Exp ECdr::step() {
  if (!e->is_value()) {
    return std::make_shared<ECdr>(e->step());
  } else {
    Shared_EList l = e->get_list();
    std::vector<Shared_Exp> e_list = l->get_e_list();
    e_list.erase(e_list.begin(), e_list.begin() + 1);
    return std::make_shared<EList>(e_list, l->get_t());
  }
}

Shared_Exp ECdr::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<ECdr>(this->e->substitute(var, e));
}

std::string ECdr::string_of_exp() { return "cdr (" + e->string_of_exp() + ")"; }

Shared_Typ ECdr::typecheck(context_t context) {
  Shared_Typ t = e->typecheck(context);
  if (dynamic_cast<TList *>(t.get()) == nullptr) {
    type_error(string_of_exp(), "{t}", t->get_type());
  } else {
    return t;
  }

  return nullptr;
}

/******************************************************************************
                               EEmpty Implementaion
*******************************************************************************/

EEmpty::EEmpty(Shared_Exp _e) : e(_e) {}

Shared_Exp EEmpty::step() {
  if (!e->is_value()) {
    return std::make_shared<EEmpty>(e->step());
  }
  return std::make_shared<EBool>(e->get_list()->get_e_list().size() == 0);
}

Shared_Exp EEmpty::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EEmpty>(this->e->substitute(var, e));
}

std::string EEmpty::string_of_exp() {
  return "empty? (" + e->string_of_exp() + ")";
}

Shared_Typ EEmpty::typecheck(context_t context) {
  Shared_Typ t = e->typecheck(context);
  if (dynamic_cast<TList *>(t.get()) == nullptr) {
    type_error(string_of_exp(), "{t}", t->get_type());
  } else {
    return std::make_shared<TBool>();
  }

  return nullptr;
}

/******************************************************************************
                               ERef Implementaion
*******************************************************************************/

ERef::ERef(Shared_Exp _e) : e(_e) {}

Shared_Exp ERef::step() {
  if (!e->is_value()) {
    return std::make_shared<ERef>(e->step());
  }
  size_t n = heap.size();
  heap.insert({n, e});
  return std::make_shared<EPtr>(n);
}

Shared_Exp ERef::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<ERef>(this->e->substitute(var, e));
}

std::string ERef::string_of_exp() { return "ref (" + e->string_of_exp() + ")"; }

Shared_Typ ERef::typecheck(context_t context) {
  return std::make_shared<TRef>(e->typecheck(context));
}

/******************************************************************************
                               EPtr Implementaion
*******************************************************************************/

EPtr::EPtr(size_t _n) : n(_n) {}

Shared_Exp EPtr::step() { return std::make_shared<EPtr>(n); }

Shared_Exp EPtr::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EPtr>(n);
}

std::string EPtr::string_of_exp() { return "ptr(" + std::to_string(n) + ")"; }

Shared_Typ EPtr::typecheck(context_t context) {
  std::cerr << "Fatal: typecheck should happen before evaluation" << std::endl;
  exit(1);
}

bool EPtr::is_value() { return true; }

Shared_EPtr EPtr::get_ptr() { return std::make_shared<EPtr>(n); }

size_t EPtr::get_addr() { return n; }

/******************************************************************************
                               EDeref Implementaion
*******************************************************************************/

EDeref::EDeref(Shared_Exp _e) : e(_e) {}

Shared_Exp EDeref::step() {
  if (!e->is_value()) {
    return std::make_shared<EDeref>(e->step());
  }
  Shared_EPtr p = e->get_ptr();
  return heap[p->get_addr()];
}

Shared_Exp EDeref::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EDeref>(this->e->substitute(var, e));
}

std::string EDeref::string_of_exp() { return "!(" + e->string_of_exp() + ")"; }

Shared_Typ EDeref::typecheck(context_t context) {
  Shared_Typ t = e->typecheck(context);
  if (dynamic_cast<TRef *>(t.get()) != nullptr) {
    return t->get_first_subtype();
  } else {
    type_error(string_of_exp(), "<t>", t->get_type());
  }
  return nullptr;
}

/******************************************************************************
                               EAssign Implementaion
*******************************************************************************/

EAssign::EAssign(Shared_Exp _e1, Shared_Exp _e2) : e1(_e1), e2(_e2) {}

Shared_Exp EAssign::step() {
  if (!e1->is_value()) {
    return std::make_shared<EAssign>(e1->step(), e2);
  } else if (!e2->is_value()) {
    return std::make_shared<EAssign>(e1, e2->step());
  }
  Shared_EPtr p = e1->get_ptr();
  heap[p->get_addr()] = e2;
  return std::make_shared<EUnit>();
}

Shared_Exp EAssign::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EAssign>(e1->substitute(var, e),
                                   e2->substitute(var, e));
}

std::string EAssign::string_of_exp() {
  return e1->string_of_exp() + " := " + e2->string_of_exp();
}

Shared_Typ EAssign::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  Shared_Typ t2 = e2->typecheck(context);
  Shared_Typ t1_1 = t1->get_first_subtype();
  if (dynamic_cast<TRef *>(t1.get()) == nullptr) {
    type_error(string_of_exp(), "<t>", t1->get_type());
  } else if (*t1_1.get() != *t2.get()) {
    type_error(string_of_exp(), t1_1->get_type(), t2->get_type());
  } else {
    return std::make_shared<TUnit>();
  }
  return nullptr;
}

/******************************************************************************
                               ESeq Implementaion
*******************************************************************************/

ESeq::ESeq(Shared_Exp _e1, Shared_Exp _e2) : e1(_e1), e2(_e2) {}

Shared_Exp ESeq::step() {
  if (!e1->is_value()) {
    return std::make_shared<ESeq>(e1->step(), e2);
  }
  return e2;
}

Shared_Exp ESeq::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<ESeq>(e1->substitute(var, e), e2->substitute(var, e));
}

std::string ESeq::string_of_exp() {
  return e1->string_of_exp() + ";" + e2->string_of_exp();
}

Shared_Typ ESeq::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  Shared_Typ t2 = e2->typecheck(context);
  return t2;
}

std::pair<cexp::Shared_Exp, std::vector<Shared_Stmt>> ESeq::convert() {
  auto subexp1 = factor_subexp(e1);
  auto subexp2 = factor_subexp(e2);
  std::vector<Shared_Stmt> v(std::get<1>(subexp1));
  auto v2 = std::get<1>(subexp2);
  v.insert(v.begin(), v2.begin(), v2.end());
  v.push_back(std::get<2>(subexp1));
  v.push_back(std::get<2>(subexp2));
  return {std::make_shared<cexp::EVar>(std::get<0>(subexp2)), v};
}

/******************************************************************************
                               EWhile Implementaion
*******************************************************************************/

EWhile::EWhile(Shared_Exp _e1, Shared_Exp _e2, Shared_Exp _e_temp)
    : e1(_e1), e2(_e2), e_temp(_e_temp) {}

Shared_Exp EWhile::step() {
  if (!e1->is_value()) {
    return std::make_shared<EWhile>(e1->step(), e2, e_temp);
  }

  if (e1->get_bool()) {
    return std::make_shared<ESeq>(e2,
                                  std::make_shared<EWhile>(e_temp, e2, e_temp));
  } else {
    return std::make_shared<EUnit>();
  }
}

Shared_Exp EWhile::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EWhile>(e1->substitute(var, e),
                                  e2->substitute(var, e),
                                  e_temp->substitute(var, e));
}

std::string EWhile::string_of_exp() {
  return "while (" + e1->string_of_exp() + ") {" + e2->string_of_exp() + "}";
}

Shared_Typ EWhile::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  Shared_Typ t2 = e2->typecheck(context);
  if (dynamic_cast<TBool *>(t1.get()) == nullptr) {
    type_error(string_of_exp(), "Boolean", t1->get_type());
  }
  return std::make_shared<TUnit>();
}
