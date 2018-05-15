#include <c_type.hpp>

using namespace ctyp;

//********************************TInt Implementation********************************//

class TInt : public Typ {
public:
  TInt();
  std::string string_of_typ() {
    return "int";
  }
};

//********************************TBool Implementation*******************************//

class TBool : public Typ {
public:
  TBool();
  std::string string_of_typ() {
    return "bool";
  }
}
