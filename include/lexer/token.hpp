#ifndef TOKEN_HPP
#define TOKEN_HPP

typedef struct {
  enum { LParen, RParen, Plus, Subtract, Divide, Multiply, Number } id;
  int data;
} Token;

#endif
