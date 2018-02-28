#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include "token.hpp"
#include <memory>
#include <iostream>

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

/******************************************************************************
                               Exp Header
*******************************************************************************/

class Exp {
public:
  virtual std::shared_ptr<Exp> step() = 0;
  virtual std::shared_ptr<Exp> substitute(std::string var, std::shared_ptr<Exp> t) = 0;
  virtual std::string string_of_exp() = 0;

  virtual bool is_value() { return false; }
  virtual bool is_bool() { return false; }
  virtual bool is_int() { return false; }
  virtual bool is_float() {return false; }
  virtual bool is_NaN() { return false; }
  virtual bool is_var() { return false; }
  virtual bool is_func() { return false; }


  virtual bool get_bool() {
    std::cerr << "Expecting a boolean!\n";
    exit(1);
  }
  virtual int get_int() {
    std::cerr << "Expecting an integer!\n";
    exit(1);
  }
  virtual std::string get_NaN() {
    std::cerr << "Expecting an integer!\n";
    exit(1);
  }
  virtual double get_float() {
    std::cerr << "Expecting a float!\n";
    exit(1);
  }
  virtual std::string get_var() {
    std::cerr << "Expecting a variable!\n";
    exit(1);
  }
  virtual std::shared_ptr<EFunc> get_func() {
    std::cerr << "Expecting a boolean!\n";
    exit(1);
  }
  virtual ~Exp(){};
};

/******************************************************************************
                               EOperator Header
*******************************************************************************/

class EOperator : public Exp {
private:
  TokenKind id;
  std::shared_ptr<Exp> e1, e2;
  std::shared_ptr<Exp> evaluate_num(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2, bool is_int);

public:
  EOperator(TokenKind _id, std::shared_ptr<Exp> _e1, std::shared_ptr<Exp> _e2);
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, std::shared_ptr<Exp> t);
  std::string string_of_exp();
};

/******************************************************************************
                               EComp Header
*******************************************************************************/

class EComp : public Exp {
private:
  TokenKind id;
  std::shared_ptr<Exp> e1, e2;
  std::shared_ptr<Exp> evaluate_bool(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2);

public:
  EComp(TokenKind _id, std::shared_ptr<Exp> _e1, std::shared_ptr<Exp> _e2);
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, std::shared_ptr<Exp> t);
  std::string string_of_exp();
};


/******************************************************************************
                               ELit Header
*******************************************************************************/

class ELit : public Exp {
private:
  bool _is_int;
  bool _is_NaN;
  int int_data;
  double float_data;
public:
  ELit(bool __is_int, int _int_data, double _float_data, bool __is_NaN);
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, std::shared_ptr<Exp> e);
  std::string string_of_exp();

  bool is_value();
  bool is_int();
  int get_int();
  bool is_float();
  double get_float();
  bool is_NaN();
  std::string get_NaN();
};

/******************************************************************************
                               EBool Header
*******************************************************************************/

class EBool : public Exp {
private:
  bool data;
public:
  EBool(bool _data);
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, std::shared_ptr<Exp> e);
  std::string string_of_exp();
  bool is_value();
  bool is_bool();
  bool get_bool();
};

/******************************************************************************
                               EVar Header
*******************************************************************************/

class EVar : public Exp {
private:
  std::string data;

public:
  EVar(std::string _data);
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, std::shared_ptr<Exp> e);
  std::string string_of_exp();
  bool is_value();
  bool is_var();
  std::string get_var();
};

/******************************************************************************
                               EFunc Header
*******************************************************************************/

class EFunc : public Exp {
private:
  std::string param;
  std::shared_ptr<Exp> e;
  bool is_rec;
  std::string id;

public:
  EFunc(std::string _param, std::shared_ptr<Exp> _e, bool _is_rec, std::string _id);
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, std::shared_ptr<Exp> e);
  std::string string_of_exp();

  bool is_value();
  bool is_func();
  std::shared_ptr<EFunc> get_func();
  std::shared_ptr<Exp> get_function_body();
  std::string get_param();
  bool get_is_rec();
  std::string get_id();
};

/******************************************************************************
                               EIf Header
*******************************************************************************/

class EIf : public Exp {
private:
  std::shared_ptr<Exp> e1, e2, e3;

public:
  EIf(std::shared_ptr<Exp> _e1, std::shared_ptr<Exp> _e2,
      std::shared_ptr<Exp> _e3);
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, std::shared_ptr<Exp> t);
  std::string string_of_exp();
};

/******************************************************************************
                               ELet Header
*******************************************************************************/

class ELet : public Exp {
private:
  std::string var;
  std::shared_ptr<Exp> e1, e2;

public:
  ELet(std::string _var, std::shared_ptr<Exp> _e1, std::shared_ptr<Exp> _e2);
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, std::shared_ptr<Exp> t);
  std::string string_of_exp();
};

/******************************************************************************
                               EApp Header
*******************************************************************************/

class EApp : public Exp {
private:
  std::shared_ptr<Exp> function;
  std::shared_ptr<Exp> e;


public:
  EApp(std::shared_ptr<Exp> _function, std::shared_ptr<Exp> _e);
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, std::shared_ptr<Exp> t);
  std::string string_of_exp();
};

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

/******************************************************************************
                               Helper
*******************************************************************************/

std::shared_ptr<Exp> evaluate(std::shared_ptr<Exp> exp, bool print_step);

#endif
