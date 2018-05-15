#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "global.hpp"
#include "token.hpp"
#include "type.hpp"
#include <iostream>
#include <memory>
#include <vector>

using namespace cexp;
using namespace ctyp;


/************* Print to C file *******************/

std::string string_of_blk(std::vector<Shared_Stmt> stmt_list, std::string ret);

std::string string_of_arg(c_arg_t arg);

std::string string_of_fn(c_function_t func);

std::string string_of_prog();

/************** Convert Functions ****************/

c_arg_t conv_arg(arg_t arg);

c_function_t conv_fn(function_t func);

c_global_function_t conv_prog(global_function_t functions);

/*************************************************/

namespace cexp {

/******************************************************************************
                               Exp Header
*******************************************************************************/

class Exp {
public:
  virtual std::string string_of_exp() = 0;
  virtual ~Exp(){};
};

/******************************************************************************
                               EOperator Header
*******************************************************************************/

class EOperator : public Exp {
private:
  TokenKind id;
  Shared_Exp e1;
  Shared_Exp e2;
public:
  EOperator(TokenKind _id, Shared_Exp _e1, Shared_Exp _e2);
  std::string string_of_exp();
};

/******************************************************************************
                               ELit Header
*******************************************************************************/

class ELit : public Exp {
private:
  int data;

public:
  ELit(int _data);

  std::string string_of_exp();
};

/******************************************************************************
                               EBool Header
*******************************************************************************/

class EBool : public Exp {
private:
  bool data;

public:
  EBool(bool _data);

  std::string string_of_exp();
};

/******************************************************************************
                               EVar Header
*******************************************************************************/

class EVar : public Exp {
private:
  std::string data;

public:
  EVar(std::string _data);

  std::string string_of_exp();
};


/******************************************************************************
                               EIf Header
*******************************************************************************/

class EIf : public Exp {
private:
  Shared_Exp e1, e2, e3;

public:
  EIf(Shared_Exp _e1, Shared_Exp _e2, Shared_Exp _e3);

  std::string string_of_exp();
};


/******************************************************************************
                               EApp Header
*******************************************************************************/

class EApp : public Exp {
private:
  std::string id;
  std::vector<Shared_Exp> v;

public:
  EApp(std::string _id, std::vector<Shared_Exp> _v);

  std::string string_of_exp();
};

}

#endif
