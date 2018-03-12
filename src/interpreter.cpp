#include "expression.hpp"
#include "interpreter.hpp"
#include "token.hpp"
#include "parser_driver.h"
#include "global.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

void interpret(Shared_Exp root, bool print_step) {
  context_t context;
  root->typecheck(context);
  Shared_Exp result = evaluate(root, print_step);
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
    std::cout << result->string_of_exp() << std::endl;
  } else if (result->is_pair()) {
    std::cout << result->string_of_exp() << std::endl;
  } else if (result->is_list()) {
    std::cout << result->string_of_exp() << std::endl;
  } else if (result->is_unit()) {
    return;
  } else {
    std::cerr << "Debug: Error! Shoule be evaluated to a value" << std::endl;
    std::cerr << result->string_of_exp() << std::endl;
    exit(1);
  }
}

void include_header() {
  parser_driver d("-");
  for(int i = 0; i < header.size(); i++) {
    std::cout << header[i] << std::endl;
    d = parser_driver(header[i]);
    std::cout << header[i] << std::endl;
    Shared_Exp prog = d.parse();
    std::cout << header[i] << std::endl;
    // interpret(prog, false);
  }
}
