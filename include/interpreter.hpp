class Exp;

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include "expression.hpp"
#include "token.hpp"
#include <vector>

std::vector<Token> lex();

Shared_Exp consume(std::vector<Token> &tokens, int &pos, TokenKind t,
                   bool is_binary);

Shared_Exp parse(std::vector<Token> &tokens, int &pos);

void interpret(Shared_Exp);

#endif
