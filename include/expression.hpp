#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include "token.hpp"
#include <memory>

class Exp {
public:
  virtual Result evaluate() = 0;
  virtual std::string string_of_exp() = 0;
  virtual ~Exp(){};
};

class EOperator : public Exp {
private:
  TokenKind id;
  std::shared_ptr<Exp> e1, e2;
  
public:
  EOperator(TokenKind t, std::shared_ptr<Exp> l, std::shared_ptr<Exp> r);
  Result evaluate();
  std::string string_of_exp();
};

class ELit : public Exp {
private:
  Token data;

public:
  ELit(Token val);
  Result evaluate();
  std::string string_of_exp();
};

class EIf : public Exp {
private:
  std::shared_ptr<Exp> e1, e2, e3;

public:
  EIf(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2,
      std::shared_ptr<Exp> e3);
  Result evaluate();
  std::string string_of_exp();
};

// Alias for shared_ptr
typedef std::shared_ptr<EOperator> Shared_EOperator;
typedef std::shared_ptr<ELit> Shared_ELit;
typedef std::shared_ptr<Exp> Shared_Exp;

#endif
