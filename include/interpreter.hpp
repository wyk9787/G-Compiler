#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <string>
#include <vector>
#include "expression.hpp"
#include "token.hpp"

using namespace fexp;

Shared_Exp interpret(Shared_Exp root, bool print_step);

#endif
