#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "expression.hpp"
#include "token.hpp"
#include <vector>
#include <string>

using namespace fexp;

Shared_Exp interpret(Shared_Exp root, bool print_step);

#endif
