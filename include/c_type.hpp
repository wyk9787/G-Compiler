#ifndef C_TYPE_HPP
#define C_TYPE_HPP

#include <expression.hpp>
#include <unordered_map>
#include <iostream>
#include <typeinfo>

class Typ;
class TInt;
class TBool;

namespace ctyp {

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
}

#endif
