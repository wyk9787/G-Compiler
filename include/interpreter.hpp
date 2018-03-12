#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "expression.hpp"
#include "token.hpp"
#include <vector>
#include <string>

void interpret(Shared_Exp, bool print_step);

void include_header();

#endif
