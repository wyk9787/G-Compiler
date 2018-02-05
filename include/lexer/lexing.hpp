class Exp;

#ifndef LEXING_HPP
#define LEXING_HPP
#include "expression.hpp"
#include "token.hpp"
#include <vector>

typedef std::shared_ptr<EOperator> Shared_EOperator;
typedef std::shared_ptr<ELit> Shared_ELit;
typedef std::shared_ptr<Exp> Shared_Exp;

std::vector<Token> lex();

Shared_Exp parse(std::vector<Token> tokens, int &pos);

int interpret(Shared_Exp);

#endif
