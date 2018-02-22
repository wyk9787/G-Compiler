#include "expression.hpp"
#include "interpreter.hpp"
#include "parser_driver.h"
#include "token.hpp"

#include <cctype>
#include <cstring>
#include <fcntl.h>
#include <getopt.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

static std::string usage =
    "Usage: ./build/compiler [-h|--help] "
    "[-l|--length] [-f|--filename "
    "<filename>] [-L|--lex] [-P|--PARSE] [-p|--parse]\n"
    "NOTE:[-f|--filename <filename>] has to present to take the input file\n";

static std::string flags =
    "Available flags:\n"
    "\t-f --file\t\ttake one argument as the filename of the input\n"
    "\t-p --parse\t\tgenerate the abstract syntax tree from parsing\nThis is "
    "the only option that will stop the compiler from interpreting the "
    "output\n"
    "\t-P --PARSE\t\tgenerate EXTREMELY verbose parsing stages (Debug use "
    "only)\n"
    "\t-L --lex\t\tgenerate the tokens and matching rules in .l file\n"
    "\t-l --length\t\tprints the lengths of each of the arguments\n"
    "\t-h --help\t\tprints the help message.\n";

void processing(int argc, char **argv);

int main(int argc, char **argv) { processing(argc, argv); }

void processing(int argc, char **argv) {
  if (argc == 1) {
    std::cout << usage << std::endl;
  }
  parser_driver driver("-"); // Default as stdin input
  int long_optind = 0;
  static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                         {"length", no_argument, 0, 'l'},
                                         {"file", required_argument, 0, 'f'},
                                         {"parse", no_argument, 0, 'p'},
                                         {"PARSE", no_argument, 0, 'P'},
                                         {"lex", no_argument, 0, 'L'},
                                         {0, 0, 0, 0}};
  std::vector<char> options; // Store all the options into the vector options
  char *opt_arg;
  int c;
  while ((c = getopt_long(argc, argv, "lhf:LpP", long_options, &long_optind)) !=
         -1) {
    options.push_back(c);
    if (c == 'f') {
      opt_arg = strdup(optarg);
    }
  }
  Shared_Exp prog;
  // If '-p' presents, then we will not interpret the output
  bool parse_only = find(options.begin(), options.end(), 'p') != options.end();
  for (size_t i = 0; i < options.size(); i++) { // Processing flags
    c = options[i];
    if (c == 'l') { // -l --length
      for (int i = optind; i < argc; i++) {
        printf("%lu\n", strlen(argv[i]));
      }
    } else if (c == 'h') { // -h --help
      std::cout << usage << std::endl;
      std::cout << flags << std::endl;
    } else if (c == 'p') { // -p --parse
      prog = driver.parse();
      std::cout << prog->string_of_exp() << std::endl;
      return;
    } else if (c == 'P') { // -P --PARSE
      driver.trace_parsing = true;
    } else if (c == 'L') { // -L --lex
      driver.trace_scanning = true;
    } else if (c == 'f') { // -f --file
      driver = parser_driver(opt_arg);
    } else if (c == '?') {
      std::cout << "Please use --help for help page" << std::endl;
      exit(1);
    }
  }
  if (!parse_only) {
    prog = driver.parse();
    interpret(prog);
  }
}
