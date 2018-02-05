#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include "token.hpp"
#include <memory>

class Exp {
public:
  virtual int evaluate() = 0;
  virtual ~Exp() {};
};

class EOperator : public Exp {
private:


public:
  std::shared_ptr<Exp> e1, e2;
  enum { Plus, Subtract, Multiply, Divide } id;
  EOperator(Token t, std::shared_ptr<Exp> l, std::shared_ptr<Exp> r);
  int evaluate();
};

class ELit : public Exp {
private:
  int data;

public:
  ELit(int val);
  int evaluate();
};

#endif
