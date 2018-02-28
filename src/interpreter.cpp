#include "expression.hpp"
#include "interpreter.hpp"
#include "token.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

void interpret(Shared_Exp root) {
  Shared_Exp result = evaluate(root);
  assert(result->is_value() == true);
  if (result->is_NaN()) {
    std::cout << result->get_NaN() << std::endl;
  } else if (result->is_int()) {
    std::cout << result->get_int() << std::endl;
  } else if (result->is_float()) {
    std::cout << result->get_float() << std::endl;
  } else if (result->is_bool()) {
    std::cout << (result->get_bool() ? "true" : "false") << std::endl;
  } else if (result->is_var()) {
    std::cout << result->get_var() << std::endl;
  } else if (result->is_func()) {
    std::cout << result->get_func()->string_of_exp() << std::endl;
  } else {
    std::cerr << "Debug: Error! Shoule be evaluated to a value" << std::endl;
    exit(1);
  }
}

/*******************************************************************************
NOTE: Everything down below is a hand-written parser and lexer for assignment1
and assignment2
*******************************************************************************/

// Shared_Exp consume(std::vector<Token> &tokens, int &pos, TokenKind t,
//                    bool is_binary) {
//   Token token = tokens[pos];
//   if (token.id == t) {
//     pos++;
//     if (is_binary) {
//       Shared_Exp e1 = parse(tokens, pos);
//       Shared_Exp e2 = parse(tokens, pos);
//       consume(tokens, pos, RParen, 0);
//       return std::make_shared<EOperator>(token.id, e1, e2);
//     } else {
//       return nullptr;
//     }
//   } else {
//     std::cerr << "Unexpected String: " << enum_string[token.id] << std::endl;
//     exit(1);
//   }
// }
//
// Shared_Exp parse(std::vector<Token> &tokens, int &pos) {
//   Shared_Exp cur;
//   Token token = tokens[pos];
//   int id = token.id;
//   if (pos < tokens.size()) {
//     if (id == LParen) {
//       consume(tokens, pos, LParen, false);
//       token = tokens[pos];
//       id = token.id;
//       if (id == Plus || id == Subtract || id == Divide || id == Multiply ||
//           id == Less_Than) {
//         return consume(tokens, pos, token.id, true);
//       } else if (id == If) {
//         consume(tokens, pos, If, false);
//         Shared_Exp e1 = parse(tokens, pos);
//         Shared_Exp e2 = parse(tokens, pos);
//         Shared_Exp e3 = parse(tokens, pos);
//         consume(tokens, pos, RParen, false);
//         return std::make_shared<EIf>(e1, e2, e3);
//       } else {
//         std::cerr << "Unexpected String: " << enum_string[token.id]
//                   << std::endl;
//         exit(1);
//       }
//     } else if (id == Num_Int || id == Num_Float || id == True || id == False
//     ||
//                id == Lit_NaN) {
//       consume(tokens, pos, token.id, false);
//       return std::make_shared<ELit>(token);
//     } else {
//       std::cerr << "Unexpected String: " << enum_string[token.id] <<
//       std::endl;
//       exit(1);
//     }
//   } else {
//     fprintf(stderr, "Expected a token\n");
//     exit(1);
//   }
//   return nullptr;
// }
//
// std::vector<Token> lex() {
//   char c;
//   bool next = false;
//   std::vector<Token> tokens;
//   while (next || ((c = fgetc(stdin)) != EOF)) {
//     next = false;
//     Token t;
//     // std::cout << c << std::endl;
//     if (c == '(') {
//       t.id = LParen;
//     } else if (c == ')') {
//       t.id = RParen;
//     } else if (c == '+') {
//       t.id = Plus;
//     } else if (c == '-') {
//       t.id = Subtract;
//     } else if (c == '*') {
//       t.id = Multiply;
//     } else if (c == '/') {
//       t.id = Divide;
//     } else if (c == 't') {
//       char next[4];
//       if (fgets(next, 4, stdin) && !strcmp(next, "rue")) {
//         t.id = True;
//         t.bool_data = true;
//       } else {
//         fprintf(stderr, "Unknown token presents.\n");
//         exit(1);
//       }
//     } else if (c == 'f') {
//       char next[5];
//       if (fgets(next, 5, stdin) && !strcmp(next, "alse")) {
//         t.id = False;
//         t.bool_data = false;
//       } else {
//         fprintf(stderr, "Unknown token presents.\n");
//         exit(1);
//       }
//     } else if (c == 'i') {
//       if (((c = fgetc(stdin)) != EOF) && c == 'f') {
//         t.id = If;
//       } else {
//         fprintf(stderr, "Unknown token presents.\n");
//         exit(1);
//       }
//     } else if (c == '<') {
//       if (((c = fgetc(stdin)) != EOF) && c == '=') {
//         t.id = Less_Than;
//       } else {
//         fprintf(stderr, "Unknown token presents.\n");
//         exit(1);
//       }
//     } else if (isdigit(c)) {
//       // This token can be an integer or a floating number
//
//       // Get the part before dot
//       int val = c - '0';
//       c = fgetc(stdin);
//       while (isdigit(c)) {
//         val *= 10;
//         val += c - '0';
//         c = fgetc(stdin);
//       }
//
//       int prev = val;
//       if (c == '.') { // if it is a float
//         c = fgetc(stdin);
//         val = c - '0';
//         double decimal = 0;
//         int digit = 1;
//         while (isdigit(c)) {
//           decimal += (c - '0') * pow(0.1, digit++);
//           c = fgetc(stdin);
//         }
//         decimal += prev;
//         t.id = Num_Float;
//         t.float_data = decimal;
//       } else { // if it is an integer
//         t.id = Num_Int;
//         t.int_data = prev;
//       }
//       next = true;
//     } else if (isspace(c)) {
//       continue;
//     } else if (c == 'N') {
//       char next[5];
//       if (fgets(next, 3, stdin) && !strcmp(next, "aN")) {
//         t.id = Lit_NaN;
//       } else {
//         fprintf(stderr, "Unknown token presents.\n");
//         exit(1);
//       }
//     }
//
//     else {
//       fprintf(stderr, "Unknown token presents.\n");
//       exit(1);
//     }
//     tokens.push_back(t);
//   }
//
//   // for (int i = 0; i < tokens.size(); i++) {
//   //   std::cout << tokens[i].data << " ";
//   // }
//   // printf("\n");
//   // for (int i = 0; i < tokens.size(); i++) {
//   //   std::cout << enum_string[tokens[i].id] << " ";
//   // }
//   // printf("\n");
//   return tokens;
// }
