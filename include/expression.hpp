#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include "token.hpp"
#include <memory>

/******************************************************************************
                               Exp Header
*******************************************************************************/

class Exp {
public:
  virtual Token evaluate() = 0;
  virtual std::shared_ptr<Exp> step() = 0;
  virtual std::shared_ptr<Exp> substitute(std::string var, Token t) = 0;
  virtual std::string string_of_exp() = 0;
  virtual ~Exp(){};
};

/******************************************************************************
                               EOperator Header
*******************************************************************************/

class EOperator : public Exp {
private:
  TokenKind id;
  std::shared_ptr<Exp> e1, e2;
  void evaluate_num(Token &result, Token e1_result, Token e2_result,
                    bool is_int);

public:
  EOperator(TokenKind _id, std::shared_ptr<Exp> _e1, std::shared_ptr<Exp> _e2);
  Token evaluate();
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, Token t);
  std::string string_of_exp();
};

/******************************************************************************
                               ELit Header
*******************************************************************************/

class ELit : public Exp {
private:
  Token data;

public:
  ELit(Token val);
  Token evaluate();
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, Token t);
  std::string string_of_exp();
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
  Token evaluate();
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, Token t);
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
  Token evaluate();
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, Token t);
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
  Token evaluate();
  std::shared_ptr<Exp> step();
  std::shared_ptr<Exp> substitute(std::string var, Token t);
  std::string string_of_exp();
};

/******************************************************************************
                               Helper Function
*******************************************************************************/

bool is_value(std::shared_ptr<Exp> e);

/******************************************************************************
                               Alias for shared_ptr
*******************************************************************************/
typedef std::shared_ptr<Exp> Shared_Exp;
typedef std::shared_ptr<EOperator> Shared_EOperator;
typedef std::shared_ptr<ELit> Shared_ELit;
typedef std::shared_ptr<ELet> Shared_ELet;
typedef std::shared_ptr<EApp> Shared_EApp;

#endif
