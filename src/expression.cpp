#include "expression.hpp"
#include "interpreter.hpp"
#include <iostream>
#include <stdlib.h>

/******************************************************************************
                        EOperator Implementaion
*******************************************************************************/
EOperator::EOperator(TokenKind _id, Shared_Exp _e1, std::shared_ptr<Exp> _e2)
    : id(_id), e1(_e1), e2(_e2) {}

void EOperator::evaluate_num(Token &result, Token e1_result, Token e2_result,
                             bool is_int) {
  auto e1_data = is_int ? e1_result.int_data : e1_result.float_data;
  auto e2_data = is_int ? e2_result.int_data : e2_result.float_data;
  if (!is_int) {
    if (e1_result.id == Int) { // e1 is Int
      e1_data = (double)e1_result.int_data;
    } else if (e2_result.id == Int) { // e2 is Int
      e2_data = (double)e2_result.int_data;
    }
  }
  auto temp_data = e1_data + e2_data;
  bool is_bool = false;
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
      result.id = NaN;
    } else {
      fprintf(stderr, "Fatal: Division by 0\n");
      exit(1);
    }
    break;
  }
  case Leq:
    result.bool_data = e1_data <= e2_data;
    is_bool = true;
    break;
  case Less:
    result.bool_data = e1_data < e2_data;
    is_bool = true;
    break;
  case Equal:
    result.bool_data = e1_data == e2_data;
    is_bool = true;
    break;
  case Greater:
    result.bool_data = e1_data > e2_data;
    is_bool = true;
    break;
  case Geq:
    result.bool_data = e1_data >= e2_data;
    is_bool = true;
    break;
  default:
    fprintf(stderr, "This should never happen!\nDebug: EOp(1)\n");
    exit(1);
    break;
  }
  if (is_bool) {
    result.id = Bool;
  } else {
    if (is_int)
      result.int_data = temp_data;
    else
      result.float_data = temp_data;
  }
}

Token EOperator::evaluate() {
  Token e1_result = e1->evaluate();
  Token e2_result = e2->evaluate();
  Token result;
  if (e1_result.id == Int && e2_result.id == Int) {
    result.id = Int;
    evaluate_num(result, e1_result, e2_result, true);
  } else if (e1_result.id == Bool || e2_result.id == Bool) {
    std::cerr << "Unexpected boolean value" << std::endl;
    exit(1);
  } else if (e1_result.id == Var || e2_result.id == Var) {
    std::cerr << "Unexpected variable" << std::endl;
    exit(1);
  } else if (e1_result.id == NaN || e2_result.id == NaN) {
    result.id = NaN;
  } else if (e1_result.id == Float || e2_result.id == Float) {
    result.id = Float;
    evaluate_num(result, e1_result, e2_result, false);
  } else {
    fprintf(stderr, "This should never happen!\nDebug: EOp(3)\n");
    exit(1);
  }
  return result;
}

Shared_Exp EOperator::step() {
  if(!is_value(e1)) {
    return std::make_shared<EOperator>(id, e1->step(), e2);
  } else if (!is_value(e2)) {
    return std::make_shared<EOperator>(id, e1, e2->step());
  } else {
    return std::make_shared<EOperator>(id, e1, e2);
  }
}

Shared_Exp EOperator::substitute(std::string var, Token t) {
  return std::make_shared<EOperator>(id, e1->substitute(var, t),
                                     e2->substitute(var, t));
}

std::string EOperator::string_of_exp() {
  return "(" + enum_string[id] + " " + e1->string_of_exp() + " " +
         e2->string_of_exp() + ")";
}

/******************************************************************************
                        ELit Implementaion
*******************************************************************************/

ELit::ELit(Token val) : data(val) {}

Token ELit::evaluate() { return data; }

Shared_Exp ELit::step() {
  return std::make_shared<ELit>(data);
}

Shared_Exp ELit::substitute(std::string var, Token t) {
  if (data.id == Var && data.var_data == var) {
    return std::make_shared<ELit>(t);
  } else if (data.id == Fun) {
    Token temp;
    temp.id = Fun;
    Func function;
    function.parameter = data.func_data.parameter;
    function.e = data.func_data.e->substitute(var, t);
    temp.func_data = function;
    return std::make_shared<ELit>(temp);
  } else {
    return std::make_shared<ELit>(data);
  }
}

std::string ELit::string_of_exp() {
  int id = data.id;
  if (data.id == Int) {
    return std::to_string(data.int_data);
  } else if (data.id == Float) {
    return std::to_string(data.float_data);
  } else if (data.id == Bool) {
    return data.bool_data ? "true" : "false";
  } else if (data.id == Var) {
    return data.var_data;
  } else if (data.id == Fun) {
    Func function = data.func_data;
    if (function.is_recursive) {
      return "(rec " + function.id + " " + function.parameter + " -> " +
             function.e->string_of_exp() + " )";
    } else {
      return "(fun " + function.parameter + " -> " +
             function.e->string_of_exp() + " )";
    }
  } else {
    return enum_string[id];
  }
}

/******************************************************************************
                        EIf Implementaion
*******************************************************************************/

EIf::EIf(std::shared_ptr<Exp> _e1, std::shared_ptr<Exp> _e2,
         std::shared_ptr<Exp> _e3)
    : e1(_e1), e2(_e2), e3(_e3) {}

Token EIf::evaluate() {
  Token e1_result = e1->evaluate();
  if (e1_result.id != Bool) {
    fprintf(stderr,
            "The first argument for the if statement should be a boolean.\n");
    exit(1);
  }
  if (e1_result.bool_data) {
    return e2->evaluate();
  } else {
    return e3->evaluate();
  }
}

Shared_Exp EIf::step() {
  if(!is_value(e1)) {
    return std::make_shared<EIf>(e1->step(), e2, e3);
  } else { // e1 is a value
    // TODO: Implement this w/ or w/o exp_to_value?
    return e1;
  }
}

Shared_Exp EIf::substitute(std::string var, Token t) {
  return std::make_shared<EIf>(e1->substitute(var, t), e2->substitute(var, t),
                               e3->substitute(var, t));
}

std::string EIf::string_of_exp() {
  return "(if " + e1->string_of_exp() + " " + e2->string_of_exp() + " " +
         e3->string_of_exp() + ")";
}

/******************************************************************************
                        ELet Implementaion
*******************************************************************************/

ELet::ELet(std::string _var, std::shared_ptr<Exp> _e1, std::shared_ptr<Exp> _e2)
    : var(_var), e1(_e1), e2(_e2) {}

Token ELet::evaluate() {
  return e2->substitute(var, e1->evaluate())->evaluate();
}

Shared_Exp ELet::step() {
  if(!is_value(e1)) {
    return std::make_shared<ELet>(var, e1->step(), e2);
  } else {
    // TODO: evaluate?
    return e2->substitute(var, e1->evaluate());
  }
}

Shared_Exp ELet::substitute(std::string var, Token t) {
  return std::make_shared<ELet>(this->var, e1->substitute(var, t),
                                e2->substitute(var, t));
}

std::string ELet::string_of_exp() {
  return "(let " + var + " = " + e1->string_of_exp() + " in " +
         e2->string_of_exp() + ")";
}

/******************************************************************************
                        EApp Implementaion
*******************************************************************************/

EApp::EApp(std::shared_ptr<Exp> _function, std::shared_ptr<Exp> _e)
    : function(_function), e(_e) {}

Token EApp::evaluate() {
  Token t = function->evaluate();
  if (t.id != Fun) {
    std::cerr << "Requires a function for function application" << std::endl;
    exit(1);
  }
  Func func_data = t.func_data;
  if (func_data.is_recursive) {
    return func_data.e->substitute(func_data.parameter, e->evaluate())
        ->substitute(func_data.id, t)
        ->evaluate();
  } else {
    return func_data.e->substitute(func_data.parameter, e->evaluate())
        ->evaluate();
  }
}

Shared_Exp EApp::step() {
  if(!is_value(function)) {
    return std::make_shared<EApp>(function->step(), e);
  } else if (!is_value(e)) {
    return std::make_shared<EApp>(function, e->step());
  } else {
    // TODO: Determine if it's a recursive call?
    return e;
  }
}

Shared_Exp EApp::substitute(std::string var, Token t) {
  return std::make_shared<EApp>(function->substitute(var, t),
                                e->substitute(var, t));
}

std::string EApp::string_of_exp() {
  return "(" + function->string_of_exp() + "(" + e->string_of_exp() + "))";
}

/******************************************************************************
                         Helper Functions
*******************************************************************************/

bool is_value(std::shared_ptr<Exp> e) {
  if(dynamic_cast<ELit*>(e.get())){ // If e is of type ELit
    return true;
  } else {
    return false;
  }
}
