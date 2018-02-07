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

void processing(int argc, char **argv) {
  int c;
  int long_optind = 0;
  static char usage[] = "Usage: ./build/apps/compiler [flags] [args]\n";
  static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                         {"length", no_argument, 0, 'l'},
                                         {"file", no_argument, 0, 'f'},
                                         {0, 0, 0, 0}};
  std::vector<char> options;
  // Store all the options into the vector options
  while ((c = getopt_long(argc, argv, "lhf", long_options, &long_optind)) !=
         -1) {
    options.push_back(c);
  }
  size_t optionsSize = options.size();
  for (int i = 0; i < optionsSize; i++) {
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
      printf("\t-l --length\t\tprints the lengths of each of the arguments\n");
      printf("\t-h --help\t\tprints the help message\n");
      exit(0);
    // -f --file
    case 'f':{
      // Copied from Charlie Curtsinger's CSC213 Shell lab starting code
      // https://github.com/csc213/shell
      int new_input = open(argv[optind], O_RDONLY);
      if (new_input == -1) {
        fprintf(stderr, "Failed to open input file %s\n", argv[1]);
        exit(1);
      }
      if (dup2(new_input, STDIN_FILENO) == -1) {
        fprintf(stderr, "Failed to set new file as input\n");
        exit(2);
      }
      break;
    }
    case '?':
      break;
    default:
      break;
    }
  }
}

int main(int argc, char **argv) {
  processing(argc, argv);
  int pos = 0;
  std::vector<Token> tokens = lex();
  Shared_Exp ast = parse(tokens, pos);
  interpret(ast);
}
