#include "c_expression.hpp"
#include "expression.hpp"
#include "interpreter.hpp"
#include "parser_driver.h"
#include "token.hpp"

#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static std::string usage =
    "Usage: ./build/compiler [-h|--help] "
    "[-l|--length] [-f|--filename "
    "<filename>]\n[-t|--translate <filename>] [-L|--lex] [-P|--PARSE] "
    "[-p|--parse] [-s|--step]\n"
    "NOTE:[-f|--filename <filename>] is required to take the input file\n";

static std::string flags =
    "Available flags:\n"
    "\t-f --file <filename>\t\ttake one argument as the filename of the input\n"
    "\t-t --translate <filename>\ttranslate the original program into a C "
    "program, saved in `filename`\n"
    "\t-p --parse\t\t\tgenerate the abstract syntax tree from parsing\n"
    "\t-P --PARSE\t\t\tgenerate EXTREMELY verbose parsing stages (Debug use "
    "only)\n"
    "\t-L --lex\t\t\tgenerate the tokens and matching rules in .l file\n"
    "\t-s --step\t\t\tprints the intermediate step of each evaluation\n"
    "\t-l --length\t\t\tprints the lengths of each of the arguments\n"
    "\t-h --help\t\t\tprints the help message.\n";

void processing(int argc, char **argv);
std::string parse_header(std::string filename);
void dump_file(std::string original_filename, std::ofstream &new_file);

int main(int argc, char **argv) { processing(argc, argv); }

void processing(int argc, char **argv) {
  if (argc == 1) {
    std::cout << usage << std::endl;
    return;
  }
  parser_driver driver("-");  // Default as stdin input
  int long_optind = 0;
  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"length", no_argument, 0, 'l'},
      {"file", required_argument, 0, 'f'},
      {"parse", no_argument, 0, 'p'},
      {"PARSE", no_argument, 0, 'P'},
      {"lex", no_argument, 0, 'L'},
      {"step", no_argument, 0, 's'},
      {"translate", required_argument, 0, 't'},
      {0, 0, 0, 0}};
  std::vector<char> options;  // Store all the options into the vector options
  char *f_arg;
  char *t_arg;
  int c;

  // NOTE: required_argument needs an colon here
  while ((c = getopt_long(argc, argv, "t:lhsf:LpP", long_options,
                          &long_optind)) != -1) {
    options.push_back(c);
    if (c == 'f') {
      f_arg = strdup(optarg);
    } else if (c == 't') {
      t_arg = strdup(optarg);
    }
  }
  Shared_Exp prog;
  std::string new_filename, c_filename;
  // If '-p' presents, then we will not interpret the output
  bool if_interpret = true;
  bool if_translate = false;
  bool print_step = false;

  if (find(options.begin(), options.end(), 'h') != options.end()) {
    std::cout << usage << std::endl;
    std::cout << flags << std::endl;
    exit(1);
  }

  if (find(options.begin(), options.end(), 'f') == options.end()) {
    std::cerr << "Requires -f for a file" << std::endl;
    exit(1);
  }
  for (size_t i = 0; i < options.size(); i++) {  // Processing flags
    c = options[i];
    if (c == 'l') {  // -l --length
      for (int i = optind; i < argc; i++) {
        printf("%lu\n", strlen(argv[i]));
      }
    } else if (c == 'p') {  // -p --parse
      prog = driver.parse();
      std::cout << prog->string_of_exp() << std::endl;
      if_interpret = false;
    } else if (c == 'P') {  // -P --PARSE
      driver.trace_parsing = true;
      prog = driver.parse();
      driver.trace_parsing = false;
      if_interpret = false;
    } else if (c == 'L') {  // -L --lex
      driver.trace_scanning = true;
      prog = driver.parse();
      driver.trace_scanning = false;
      if_interpret = false;
    } else if (c == 'f') {  // -f --file
      new_filename = parse_header(f_arg);
      driver = parser_driver(new_filename);
    } else if (c == 't') {  // -t --translate
      c_filename = t_arg;
      if_translate = true;
    } else if (c == 's') {
      print_step = true;
    } else if (c == '?') {
      std::cout << "Please use --help for help page" << std::endl;
      exit(1);
    }
  }
  if (if_interpret) {
    prog = driver.parse();
    auto exp = interpret(prog, print_step);
    std::cout << exp->string_of_exp() << std::endl;
    if (if_translate) {
      auto c_functions = conv_prog();  // Convert original program into C
      std::ofstream c_file;
      c_file.open(c_filename);
      c_file << string_of_prog(c_functions) << std::endl;
      c_file.close();
    }
  }
  if (remove(new_filename.c_str()) != 0) perror("Error deleting file");

  if (if_translate) free(t_arg);
  free(f_arg);
}

std::string parse_header(std::string filename) {
  std::string line;
  std::string new_filename = filename + ".temp";
  std::ifstream original_file(filename);
  std::ofstream new_file(new_filename);
  if (original_file.is_open()) {
    while (getline(original_file, line)) {
      if (line.find("#include") != std::string::npos) {
        int start = line.find("<");
        int end = line.find(">");
        if (start != std::string::npos && end != std::string::npos) {
          dump_file(line.substr(start + 1, end - start - 1), new_file);
        } else {
          std::cerr << "Expect format: #include <filename>\n";
          exit(1);
        }
      } else {
        new_file << line << "\n";
      }
    }
  } else {
    std::cerr << "Unable to open file\n";
    exit(1);
  }
  original_file.close();
  new_file.close();
  return new_filename;
}

void dump_file(std::string original_filename, std::ofstream &new_file) {
  std::ifstream original_file(original_filename);
  if (original_file.is_open()) {
    // Copy char by char
    while (!original_file.eof()) {
      char c = original_file.get();
      if (c != EOF) new_file << c;
    }
  } else {
    std::cerr << "Unable to open file\n";
    exit(1);
  }
  original_file.close();
}
