#include "expression.hpp"
#include "lexing.hpp"
#include "token.hpp"

#include <cctype>
#include <cstring>
#include <fcntl.h>
#include <getopt.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

static char usage[] = "Usage: ./build/apps/compiler [-h|--help] "
                      "[-f|--filename <filename>] [-L|--lex] [-p|--parse]  "
                      "[-l|--length]\n";

void processing(int argc, char **argv, std::vector<Token> &tokens);

int main(int argc, char **argv) {
  std::vector<Token> tokens;
  processing(argc, argv, tokens);
}

void processing(int argc, char **argv, std::vector<Token> &tokens) {
  if (argc == 1) { // No argument, read from stdin
    tokens = lex();
    int pos = 0;
    Shared_Exp ast = parse(tokens, pos);
    interpret(ast);
  }
  int c;
  int long_optind = 0;
  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},       {"length", no_argument, 0, 'l'},
      {"file", required_argument, 0, 'f'}, {"lex", no_argument, 0, 'L'},
      {"parse", no_argument, 0, 'p'},      {0, 0, 0, 0}};
  std::vector<char> options;
  char *opt_arg;
  // Store all the options into the vector options
  while ((c = getopt_long(argc, argv, "lhf:Lp", long_options, &long_optind)) !=
         -1) {
    options.push_back(c);
    if (c == 'f') {
      opt_arg = strdup(optarg);
    }
  }
  for (size_t i = 0; i < options.size(); i++) {
    c = options[i];
    if (c == -1)
      break;
    switch (c) {
    // -l --length
    case 'l':
      for (int i = optind; i < argc; i++) {
        printf("%lu\n", strlen(argv[i]));
      }
      exit(0);
    // -h --help
    case 'h':
      printf("%s", usage);
      printf("Available flags:\n");

      printf("\t-f --file\t\ttake one argument as the filename of the input\n");
      printf("\t-e --lex\t\tgenerate the tokens from lexing\n");
      printf(
          "\t-p --parse\t\tgenerate the abstract syntax tree from parsing\n");
      printf("\t-l --length\t\tprints the lengths of each of the arguments\n");
      printf("\t-h --help\t\tprints the help message\n");
      exit(0);
    // -f --file
    case 'f': {
      // Copied from Charlie Curtsinger's CSC213 Shell lab starting code
      // https://github.com/csc213/shell
      int new_input = open(opt_arg, O_RDONLY);
      if (new_input == -1) {
        fprintf(stderr, "Failed to open input file %s\n", opt_arg);
        free(opt_arg);
        exit(1);
      }
      free(opt_arg);
      if (dup2(new_input, STDIN_FILENO) == -1) {
        fprintf(stderr, "Failed to set new file as input\n");
        exit(2);
      }
      break;
    }
    case 'L': {
      if (tokens.size() == 0) {
        tokens = lex();
      }
      std::cout << "[";
      for (size_t i = 0; i < tokens.size(); i++) {
        int id = tokens[i].id;
        if (id == 6) { // integer
          std::cout << tokens[i].int_data;
        } else if (id == 12) { // float
          std::cout << tokens[i].float_data;
        } else {
          std::cout << enum_string[tokens[i].id];
        }
        std::cout << ", ";
      }
      std::cout << "]" << std::endl;
      break;
    }
    case 'p': {
      if (tokens.size() == 0) {
        tokens = lex();
      }
      int pos = 0;
      Shared_Exp ast = parse(tokens, pos);
      std::cout << ast->string_of_exp() << std::endl;
      break;
    }
    case '?':
      std::cout << "Please use --help for help page" << std::endl;
      exit(1);
    default:
      break;
    }
  }
}
