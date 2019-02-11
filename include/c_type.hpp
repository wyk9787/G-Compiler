#ifndef C_TYPE_HPP
#define C_TYPE_HPP

#include <iostream>
#include <typeinfo>
#include <unordered_map>

namespace ctyp {

using namespace ctyp;

//********************************Typ Header*********************************//

class Typ {
 public:
  virtual std::string string_of_typ() = 0;
};

//********************************TInt Header********************************//

class TInt : public Typ {
 public:
  TInt();
  std::string string_of_typ();
};

//********************************TBool Header*******************************//

class TBool : public Typ {
 public:
  TBool();
  std::string string_of_typ();
};

//********************************TStruct
//Header*******************************//

class TStruct : public Typ {
 private:
  std::string name;

 public:
  TStruct(std::string _name);
  std::string string_of_typ();
};
}

#endif
