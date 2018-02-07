class Exp;

#ifndef LEXING_HPP
#define LEXING_HPP
#include "expression.hpp"
#include "token.hpp"
#include <vector>

// Alias for shared_ptr
typedef std::shared_ptr<EOperator> Shared_EOperator;
typedef std::shared_ptr<ELit> Shared_ELit;
typedef std::shared_ptr<Exp> Shared_Exp;

std::vector<Token> lex();

Shared_Exp consume(std::vector<Token> &tokens, int &pos, TokenKind t,
                   bool is_binary);

Shared_Exp parse(std::vector<Token> &tokens, int &pos);

void interpret(Shared_Exp);

#endif
