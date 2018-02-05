#include "expression.hpp"
#include "lexing.hpp"
#include <stdlib.h>

EOperator::EOperator(Token t, std::shared_ptr<Exp> l, std::shared_ptr<Exp> r)
    : e1(l), e2(r) {
  switch (t.id) {
  case Token::Plus:
    this->id = EOperator::Plus;
    break;
  case Token::Subtract:
    this->id = EOperator::Subtract;
    break;
  case Token::Divide:
    this->id = EOperator::Divide;
    break;
  case Token::Multiply:
    this->id = EOperator::Multiply;
    break;
  default:
    break;
  }
}

int EOperator::evaluate() {
  switch (this->id) {
  case Plus:
    return e1->evaluate() + e2->evaluate();
  case Subtract:
    return e1->evaluate() - e2->evaluate();
  case Multiply:
    return e1->evaluate() * e2->evaluate();
  case Divide: {
    int e2_val = e2->evaluate();
    if (e2_val != 0) {
      return e1->evaluate() / e2_val;
    } else {
      // TODO: throw exception for divide by 0
      exit(2);
    }
  }

  default:
    // TODO: throw exception for no matching 0
    break;
  }
}

ELit::ELit(int val) : data(val) {}
int ELit::evaluate() {
  return data;
}
