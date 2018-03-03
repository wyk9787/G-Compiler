#include "expression.hpp"
#include "interpreter.hpp"
#include "type.hpp"
#include <iostream>
#include <stdlib.h>

std::shared_ptr<Exp> evaluate(std::shared_ptr<Exp> exp, bool print_step) {
  while(!exp->is_value()) {
    if(print_step) {
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
    e1 = e1->step();
  } else if (!e2->is_value()) {
    e2 = e2->step();
  } else {
    if(e1->is_NaN() || e2->is_NaN()) {
      return std::make_shared<ELit>(false, 0, 0, true);
    }
    if (!e1->is_int() && !e2->is_int() && !e1->is_float() && !e2->is_float()) {
      std::cerr << "Expecting a literal (integer or value)" << std::endl;
      exit(1);
    }
    bool is_int = e1->is_int() && e2->is_int();
    return evaluate_num(e1, e2, is_int);
  }
  return std::make_shared<EOperator>(id, e1, e2);
}

Shared_Exp EOperator::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EOperator>(id, e1->substitute(var, e),
                                     e2->substitute(var, e));
}

std::string EOperator::string_of_exp() {
  return "(" + e1->string_of_exp() + " " + enum_string[id] + " " + e2->string_of_exp() + ")";
}

Shared_Typ EOperator::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  Shared_Typ t2 = e2->typecheck(context);
  if(dynamic_cast<TInt*>(t1.get()) == nullptr && dynamic_cast<TFloat*>(t1.get()) == nullptr) {
    type_error(string_of_exp(), "Int or Float", t1->get_type());
  } else if (dynamic_cast<TInt*>(t2.get()) == nullptr && dynamic_cast<TFloat*>(t2.get()) == nullptr) {
    type_error(string_of_exp(), "Int or Float", t2->get_type());
  } else if (*t1.get() != *t2.get()) {
    type_error(string_of_exp(), t1->get_type(), t2->get_type());
  } else {
    return t1;
  }

  return nullptr;
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
    e1 = e1->step();
  } else if (!e2->is_value()) {
    e2 = e2->step();
  } else {
    if(e1->is_NaN() || e2->is_NaN()) {
      return std::make_shared<ELit>(false, 0, 0, true);
    }
    if (!e1->is_int() && !e2->is_int() && !e1->is_float() && !e2->is_float()) {
      std::cerr << "Expecting a literal (integer or value)" << std::endl;
      exit(1);
    }
    return evaluate_bool(e1, e2);
  }
  return std::make_shared<EComp>(id, e1, e2);
}

Shared_Exp EComp::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EComp>(id, e1->substitute(var, e),
                                     e2->substitute(var, e));
}

std::string EComp::string_of_exp() {
  return "(" + e1->string_of_exp() + " " + enum_string[id] + " " + e2->string_of_exp() + ")";
}

Shared_Typ EComp::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  Shared_Typ t2 = e2->typecheck(context);
  if(dynamic_cast<TInt*>(t1.get()) == nullptr && dynamic_cast<TFloat*>(t1.get()) == nullptr) {
    type_error(string_of_exp(), "Int or Float", t1->get_type());
  } else if (dynamic_cast<TInt*>(t2.get()) == nullptr && dynamic_cast<TFloat*>(t2.get()) == nullptr) {
    type_error(string_of_exp(), "Int or Float", t2->get_type());
  } else if (*t1.get() != *t2.get()) {
    type_error(string_of_exp(), t1->get_type(), t2->get_type());
  } else {
    return std::make_shared<TBool>();
  }

  return nullptr;
}

/******************************************************************************
                        ELit Implementaion
*******************************************************************************/

ELit::ELit(bool __is_int, int _int_data, double _float_data, bool __is_NaN)
    : _is_int(__is_int), int_data(_int_data), float_data(_float_data),
      _is_NaN(__is_NaN){};

Shared_Exp ELit::step() {
  return std::make_shared<ELit>(_is_int, int_data, float_data, _is_NaN);
}

Shared_Exp ELit::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<ELit>(_is_int, int_data, float_data, _is_NaN);
}

std::string ELit::string_of_exp() {
  return _is_NaN ? "NaN" :
         _is_int ? std::to_string(int_data) :
                   std::to_string(float_data);
}

Shared_Typ ELit::typecheck(context_t context) {
  if(_is_int)
    return std::make_shared<TInt>();
  else
    return std::make_shared<TFloat>();
}

bool ELit::is_value() { return true; }

bool ELit::is_int() { return _is_int; }

int ELit::get_int() { return int_data; }

bool ELit::is_float() { return !_is_int; }

double ELit::get_float() { return float_data; }

bool ELit::is_NaN() { return _is_NaN; }

std::string ELit::get_NaN() {return "NaN"; }

/******************************************************************************
                        EBool Implementaion
*******************************************************************************/

EBool::EBool(bool _data) : data(_data) {};

Shared_Exp EBool::step() {
  return std::make_shared<EBool>(data);
}

Shared_Exp EBool::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EBool>(data);
}

std::string EBool::string_of_exp() { return data ? "true" : "false"; }

Shared_Typ EBool::typecheck(context_t context) {
  return std::make_shared<TBool>();
}

bool EBool::is_value() { return true; }

bool EBool::is_bool() { return true; }

bool EBool::get_bool() { return data; }

/******************************************************************************
                        EVar Implementaion
*******************************************************************************/

EVar::EVar(std::string _data) : data(_data){};

Shared_Exp EVar::step() {
  return std::make_shared<EVar>(data);
}

Shared_Exp EVar::substitute(std::string var, Shared_Exp e) {
  if (var == data) {
    return e;
  } else {
    return std::make_shared<EVar>(data);
  }
}

std::string EVar::string_of_exp() { return data; }

Shared_Typ EVar::typecheck(context_t context) {
  if(context.find(data) != context.end()) {
    return context[data];
  } else {
    std::cerr << "Requires a type for " << data << std::endl;
    exit(1);
  }
}

bool EVar::is_value() { return true; }

bool EVar::is_var() { return true; }

std::string EVar::get_var() { return data; }

/******************************************************************************
                        EFunc Implementaion
*******************************************************************************/

EFunc::EFunc(std::string _param, Shared_Typ _t1, Shared_Typ _t2, Shared_Exp _e, bool _is_rec, std::string _id)
      : param(_param), t1(_t1), t2(_t2), e(_e), is_rec(_is_rec), id(_id){};

Shared_Exp EFunc::step() {
  return std::make_shared<EFunc>(param, t1, t2, e, is_rec, id);
}

Shared_Exp EFunc::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EFunc>(param, t1, t2, this->e->substitute(var, e), is_rec,
                                 id);
}

std::string EFunc::string_of_exp() {
  if (is_rec) {
    return "(rec " + id + " [" + param + " : " + t1->get_type() + "] : " + t2->get_type() + " -> " + e->string_of_exp() + ")";
  } else {
    return "(fun [" + param + " : " + t1->get_type() + "] : " + t2->get_type() + " -> " + e->string_of_exp() + ")";
  }
}

Shared_Typ EFunc::typecheck(context_t context) {
  if(is_rec) {
    context.insert({id, std::make_shared<TFunc>(t1, t2)});
  }
  context.insert({param, t1});
  Shared_Typ e_type = e->typecheck(context);
  if(*e_type.get() == *t2.get()) {
    return std::make_shared<TFunc>(t1, t2);
  } else {
    type_error(string_of_exp(), t2->get_type(), e_type->get_type());
  }
  return nullptr;
}

bool EFunc::is_value() { return true; }

bool EFunc::is_func() { return true; }

Shared_EFunc EFunc::get_func() {
  return std::make_shared<EFunc>(param, t1, t2, e, is_rec, id);
}

Shared_Exp EFunc::get_function_body() { return e; }

std::string EFunc::get_param() { return param; }

bool EFunc::get_is_rec() { return is_rec; }

std::string EFunc::get_id() { return id; }

/******************************************************************************
                               EUnit Header
*******************************************************************************/

EUnit::EUnit() {};
Shared_Exp EUnit::step() {
  return std::make_shared<EUnit>();
}
Shared_Exp EUnit::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<EUnit>();
}
std::string EUnit::string_of_exp() {
  return "()";
}
Shared_Typ EUnit::typecheck(context_t context) {
  return std::make_shared<TUnit>();
}

bool EUnit::is_value() {
  return true;
}

bool EUnit::is_unit() {
  return true;
}

/******************************************************************************
                        EIf Implementaion
*******************************************************************************/

EIf::EIf(Shared_Exp _e1, Shared_Exp _e2, Shared_Exp _e3)
    : e1(_e1), e2(_e2), e3(_e3) {}

Shared_Exp EIf::step() {
  if (!e1->is_value()) {
    e1 = e1->step();
    return std::make_shared<EIf>(e1, e2, e3);
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
  if(dynamic_cast<TBool*>(t1.get()) == nullptr) {
    type_error(string_of_exp(), "Boolean", t1->get_type());
  } else if (*t2.get() != *t3.get()) {
    type_error(string_of_exp(), t2->get_type(), t3->get_type());
  } else {
    return t2;
  }
  return nullptr;
}

std::string EIf::string_of_exp() {
  return "(if " + e1->string_of_exp() + " then " + e2->string_of_exp() + " else " +
         e3->string_of_exp() + ")";
}

/******************************************************************************
                        ELet Implementaion
*******************************************************************************/

ELet::ELet(std::string _var, Shared_Typ _t, Shared_Exp _e1, Shared_Exp _e2)
    : var(_var), t(_t), e1(_e1), e2(_e2) {}

Shared_Exp ELet::step() {
  if (!e1->is_value()) {
    e1 = e1->step();
    return std::make_shared<ELet>(var, t, e1, e2);
  } else {
    return e2->substitute(var, e1);
  }
}

Shared_Exp ELet::substitute(std::string var, Shared_Exp e) {
  return std::make_shared<ELet>(this->var, t, e1->substitute(var, e),
                                e2->substitute(var, e));
}

std::string ELet::string_of_exp() {
  return "(let [" + var + " : " + t->get_type() + "]" + " = " + e1->string_of_exp() + " in " +
         e2->string_of_exp() + ")";
}

Shared_Typ ELet::typecheck(context_t context) {
  Shared_Typ t1 = e1->typecheck(context);
  context.insert({var, t});
  Shared_Typ t2 = e2->typecheck(context);
  if(*t1.get() != *t.get()) {
    type_error(string_of_exp(), t->get_type(), t1->get_type());
  } else {
    return t2;
  }
  return nullptr;
}

/******************************************************************************
                        EApp Implementaion
*******************************************************************************/

EApp::EApp(Shared_Exp _function, Shared_Exp _e)
    : function(_function), e(_e) {}

Shared_Exp EApp::step() {
  if (!function->is_value()) {
    function = function->step();
    return std::make_shared<EApp>(function, e);
  }

  if (function->is_func()) {
    Shared_EFunc f = function->get_func();
    if (!e->is_value()) { // If the argument hasn't been evaluated yet
      e = e->step();
      return std::make_shared<EApp>(function, e);
    }
    if(f->get_is_rec()) { // Recursive function needs to substitute one more time (substitute itself)
      return f->get_function_body()->substitute(f->get_param(), e)->substitute(f->get_id(), f);
    } else {
      return f->get_function_body()->substitute(f->get_param(), e);
    }
  } else {
    std::cerr << "Expecting a function for function application" << std::endl;
    exit(1);
  }
}

Shared_Exp EApp::substitute(std::string var, Shared_Exp _e) {
  return std::make_shared<EApp>(function->substitute(var, _e), e->substitute(var, _e));
}

std::string EApp::string_of_exp() {
  return function->string_of_exp() + "(" + e->string_of_exp() + ")";
}

Shared_Typ EApp::typecheck(context_t context) {
  Shared_Typ t1 = function->typecheck(context);
  Shared_Typ t1_1 = t1->get_first_subtype();
  Shared_Typ t1_2 = t1->get_second_subtype();
  Shared_Typ t2 = e->typecheck(context);
  if(*t1_1.get() != *t2.get()) {
    type_error(string_of_exp(), t1_1->get_type(), t2->get_type());
  } else {
    return t1_2;
  }
  return nullptr;

}
