#include "statement.hpp"
#include "c_expression.hpp"

using namespace cexp;
using namespace ctyp;

class SDecl : Stmt{
public:
  SDecl(std::string _name, Shared_Typ _t, Shared_Exp _e) : name(_name), t(_t), e(_e) {}

  std::string string_of_stmt() {
    return t->get_type() + " " + name + " = " + e->string_of_exp();
  }
};

class If : Stmt{
public:
  SIf(Shared_Exp _e, std::vector<Shared_Stmt> _b1, std::vector<Shared_Stmt> b2) : e(_e), b1(_b1), b2(_b2) {}

  std::string string_of_stmt() {
    return "if ( " + e->string_of_exp() + ") { " + string_of_blk(b1) + " } else { " + string_of_blk(b2) + " }";
  }
};

class SWhile : Stmt{
public:
  SWhile(Shared_Exp _e, std::vector<Shared_Stmt> _b) : e(_e), b(_b) {}
  std::string string_of_stmt() {
    return "while ( " + e1->string_of_exp() + ") { " + string_of_blk(b) + " }"
  }
};

class SRet : Stmt{
public:
  SRet(Shared_Exp _e) : e(_e) {}
  std::string string_of_stmt() {
    return "return " + e->string_of_exp() + ";";
  }
};

class SPrint : Stmt{
public:
  SPrint(Shared_Exp _e) : e(_e) {}
  std::string string_of_stmt() {
    return "printf(\"%%d\\n\", " + e->string_of_exp() + ");"
  }
};
