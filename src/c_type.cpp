#include "c_type.hpp"

using namespace ctyp;

//********************************TInt
//Implementation********************************//

TInt::TInt() {}
std::string TInt::string_of_typ() { return "int"; }

//********************************TBool
//Implementation*******************************//

TBool::TBool() {}
std::string TBool::string_of_typ() { return "bool"; }

//********************************TStruct
//Implementation*******************************//

TStruct::TStruct(std::string _name) : name(_name) {}

std::string TStruct::string_of_typ() { return "struct " + name; }
