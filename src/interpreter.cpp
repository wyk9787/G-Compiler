#include "c_expression.hpp"
#include "expression.hpp"
#include "global.hpp"
#include "interpreter.hpp"
#include "parser_driver.h"
#include "token.hpp"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

using namespace fexp;
using namespace ftyp;

void typecheck_all() {
  for (auto function : global_functions) {
    context_t context;
    function_t func = function.second;
    arglist_t arglist = func.arglist;
    for (size_t i = 0; i < arglist.size(); i++) {
      arg_t arg = arglist[i];
      context.insert({arg.first, arg.second});
    }
    Shared_Typ t_body = func.e->typecheck(context);
    if (function.first == "main")
      continue; // The body of main do not need to match the return type
    if (*t_body.get() != *func.return_type.get()) {
      type_error("Type checking function " + function.first,
                 func.return_type->get_type(), t_body->get_type());
    }
  }
}

void interpret(Shared_Exp root, bool print_step) {
  typecheck_all();
  Shared_Exp result = evaluate(root, print_step);
  // std::cout << result->string_of_exp() << std::endl;
  auto c_functions = conv_prog();
  std::cout << string_of_prog(c_functions) << std::endl;
}
