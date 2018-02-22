#pragma once

#include <string>
#include <map>
#include <memory>
#include "parser.yy.hpp"
#include "token.hpp"
#include "expression.hpp"

#define YY_DECL yy::parser::symbol_type yylex (parser_driver &driver)

YY_DECL;

class parser_driver {
public:
    parser_driver(const std::string &f);
    virtual ~parser_driver();

    std::string file;
    bool trace_scanning;
    bool trace_parsing;
    int result;

    Shared_Exp parse();

    void error(const yy::parser::location_type& l, const std::string &m);

    // NOTE: Implemented in scanner.l
    void scan_begin();
    void scan_end();
};
