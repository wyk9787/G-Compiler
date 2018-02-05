#include "expression.hpp"
#include "lexing.hpp"
#include "token.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <cstdio>

int interpret(Shared_Exp root) {
  // EOperator* is_operator = dynamic_cast<EOperator*>(root.get());
  // if(is_operator) {
  //
  // }
  return root->evaluate();
}

Shared_Exp parse(std::vector<Token> tokens, int &pos) {
  Shared_Exp cur;
  while (pos < tokens.size()) {
    Token cur_token = tokens[pos];
    int id = cur_token.id;
    if (id == Token::LParen) {
      pos++;
    } else if (id == Token::RParen) {
      pos++;
      return cur;
    } else if (id == Token::Number) {
      cur = std::make_shared<ELit>(cur_token.data);
      pos++;
      return cur;
    } else {
      pos++;
      Shared_Exp left = parse(tokens, pos);
      Shared_Exp right = parse(tokens, pos);
      cur = std::make_shared<EOperator>(cur_token, left, right);
    }
  }
  return cur;
}

std::vector<Token> lex() {
  char c;
  bool next = false;
  std::vector<Token> tokens;
  while (next || ((c = fgetc(stdin)) != EOF)) {
    next = false;
    Token t;
    // For now, we only support nonnegative integer addition
    // TODO: Change this so that negative number can work as well.
    t.data = -1;
    if (c == '(') {
      t.id = Token::LParen;
    } else if (c == ')') {
      t.id = Token::RParen;
    } else if (c == '+') {
      t.id = Token::Plus;
    } else if (c == '-') {
      t.id = Token::Subtract;
    } else if (c == '*') {
      t.id = Token::Multiply;
    } else if (c == '/') {
      t.id = Token::Divide;
    } else if (isdigit(c)) {
      // if it is a number, continue reading the whole number
      int val = c - '0';
      c = fgetc(stdin);
      while (isdigit(c)) {
        val *= 10;
        val += c - '0';
        c = fgetc(stdin);
      }
      next = true;
      t.id = Token::Number;
      t.data = val;
    } else if (isspace(c)) {
      continue;
    }
    tokens.push_back(t);
  }
  // for (int i = 0; i < tokens.size(); i++) {
  //   std::cout << tokens[i].data << " ";
  // }
  // printf("\n");
  // for (int i = 0; i < tokens.size(); i++) {
  //   std::cout << tokens[i].id << " ";
  // }
  // printf("\n");
  return tokens;
}
