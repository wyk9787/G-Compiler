#include "parser_driver.h"

parser_driver::parser_driver(const std::string &f)
    : file(f), trace_scanning(false), trace_parsing(false) {}

parser_driver::~parser_driver() {}

Shared_Exp parser_driver::parse() {
  scan_begin();
  Shared_Exp ret;
  yy::parser parser(*this, &ret);
  parser.set_debug_level(trace_parsing);
  result = parser.parse();
  scan_end();
  return ret;
}

void parser_driver::error(const yy::parser::location_type &l,
                          const std::string &m) {
  // NOTE: Kind of a cheat here: not really using the location's filename
  std::cerr << file << ":" << l << ": " << m << std::endl;
  exit(1);
}
