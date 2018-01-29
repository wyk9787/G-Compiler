#include <cctype>
#include <cstring>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

int main(int argc, char **argv) {
  int c;
  int long_optind = 0;
  static char usage[] = "Usage: ./compiler [flags] [args]\n";
  static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                         {"length", no_argument, 0, 'l'},
                                         {0, 0, 0, 0}};
  std::vector<char> options;

  // Store all the options into the vector options
  while ((c = getopt_long(argc, argv, "lh", long_options, &long_optind)) !=
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
      break;
    // -h --help
    case 'h':
      printf("%s", usage);
      printf("Available flags: \n");
      printf("\t-l --length\t\tprints the lengths of each of the arguments \n");
      printf("\t-h --help\t\tprints the help message\n");
      break;

    case '?':
      break;

    default:
      break;
    }
  }
  // if we there is no flag, print the arguments
  if (!optionsSize) {
    while (optind < argc) {
      printf("%s\n", argv[optind++]);
    }
  }

  exit(0);
}
