class Exp;

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include "expression.hpp"
#include "token.hpp"
#include <vector>

std::vector<Token> lex();

void interpret(Shared_Exp);


/*******************************************************************************
NOTE: Everything down below is a hand-written parser and lexer for assignment1
and assignment2
*******************************************************************************/

Shared_Exp consume(std::vector<Token> &tokens, int &pos, TokenKind t,
                   bool is_binary);

Shared_Exp parse(std::vector<Token> &tokens, int &pos);



#endif
