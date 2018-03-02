#ifndef TYPE_HPP
#define TYPE_HPP

#include <expression.hpp>
#include <unordered_map>
#include <iostream>
#include <typeinfo>

class Typ;
class TInt;
class TBool;
class TFloat;
class TFunc;

void type_error(std::string expression, std::string expected,
                std::string actual);

// bool operator ==(const Shared_Typ &first, const Shared_Typ &second);

class Typ {
public:
  virtual std::string get_type() = 0;
  virtual Shared_Typ get_first_subtype() {
    std::cerr << "There is no first subtype for this type!" << std::endl;
    exit(1);
  }
  virtual Shared_Typ get_second_subtype() {
    std::cerr << "There is no second subtype for this type!" << std::endl;
    exit(1);
  }
  // virtual bool operator==(const Typ &other) const {
  //   std::cout << "Enter Typ ==" << std::endl;
  //   if (typeid(*this) != typeid(other)) {
  //     std::cout << "here" << std::endl;
  //     return false;
  //   } else {
  //     std::cout << "here1" << std::endl;
  //     return true;
  //   }
  // }
};

class TInt : public Typ {
public:
  TInt();
  std::string get_type();
  // bool operator==(const Typ &other) const;
};

class TFloat : public Typ {
public:
  TFloat();
  std::string get_type();
  // bool operator ==(const Typ &other) const;
};

class TBool : public Typ {
public:
  TBool();
  std::string get_type();
};

class TFunc : public Typ {
private:
  Shared_Typ t1;
  Shared_Typ t2;

public:
  TFunc(Shared_Typ _t1, Shared_Typ _t2);
  std::string get_type();
  Shared_Typ get_first_subtype();
  Shared_Typ get_second_subtype();
};

#endif
