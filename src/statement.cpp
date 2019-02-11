#include "statement.hpp"
#include "c_expression.hpp"

using namespace cexp;
using namespace ctyp;

SDecl::SDecl(std::string _name, Shared_Typ _t, Shared_Exp _e)
    : name(_name), t(_t), e(_e) {}

std::string SDecl::string_of_stmt() {
  return t->string_of_typ() + " " + name + " = " + e->string_of_exp() + ";";
}

SIf::SIf(Shared_Exp _e, std::vector<Shared_Stmt> _b1,
         std::vector<Shared_Stmt> _b2)
    : e(_e), b1(_b1), b2(_b2) {}

std::string SIf::string_of_stmt() {
  return "if ( " + e->string_of_exp() + ") { " + string_of_blk(b1) +
         " } else { " + string_of_blk(b2) + " }";
}

SWhile::SWhile(Shared_Exp _e, std::vector<Shared_Stmt> _b) : e(_e), b(_b) {}
std::string SWhile::string_of_stmt() {
  return "while ( " + e->string_of_exp() + ") { " + string_of_blk(b) + " }";
}

SRet::SRet(Shared_Exp _e) : e(_e) {}
std::string SRet::string_of_stmt() {
  return "return " + e->string_of_exp() + ";";
}

SPrint::SPrint(Shared_Exp _e) : e(_e) {}
std::string SPrint::string_of_stmt() {
  return "printf(\"%d\\n\", " + e->string_of_exp() + ");";
}

SAssign::SAssign(std::string _name, Shared_Exp _e) : name(_name), e(_e) {}
std::string SAssign::string_of_stmt() {
  return name + " = " + e->string_of_exp() + ";";
}

SDef::SDef(Shared_Typ _t, std::string _name) : t(_t), name(_name) {}
std::string SDef::string_of_stmt() {
  return t->string_of_typ() + " " + name + ";";
}

SStruct::SStruct(std::string _name, Shared_Stmt _s1, Shared_Stmt _s2)
    : name(_name), s1(_s1), s2(_s2) {}

std::string SStruct::string_of_stmt() {
  return "struct " + name + " {\n" + s1->string_of_stmt() + "\n" +
         s2->string_of_stmt() + "\n};";
}
