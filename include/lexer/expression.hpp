#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include "token.hpp"
#include <memory>

class Exp {
public:
  virtual Result evaluate() = 0;
  virtual ~Exp(){};
};

class EOperator : public Exp {
private:
  std::shared_ptr<Exp> e1, e2;
  TokenKind id;

public:
  EOperator(TokenKind t, std::shared_ptr<Exp> l, std::shared_ptr<Exp> r);
  Result evaluate();
};

class ELit : public Exp {
private:
  Token data;

public:
  ELit(Token val);
  Result evaluate();
};

class EIf : public Exp {
private:
  std::shared_ptr<Exp> e1, e2, e3;

public:
  EIf(std::shared_ptr<Exp> e1, std::shared_ptr<Exp> e2,
      std::shared_ptr<Exp> e3);
  Result evaluate();
};

#endif
