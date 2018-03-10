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

bool operator ==(const Typ &first, const Typ &second);
bool operator !=(const Typ &first, const Typ &second);

//********************************Typ Header*********************************//

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
  friend bool operator==(const Typ &first, const Typ &second);
  friend bool operator!=(const Typ &first, const Typ &second);

protected:
  virtual bool eq(const Typ& other) const {
    return false;
  };
};

//********************************TInt Header********************************//

class TInt : public Typ {
public:
  TInt();
  std::string get_type();

protected:
  bool eq(const Typ& other) const;
};

//********************************TFloat Header******************************//

class TFloat : public Typ {
public:
  TFloat();
  std::string get_type();

protected:
  bool eq(const Typ& other) const;
};

//********************************TBool Header*******************************//

class TBool : public Typ {
public:
  TBool();
  std::string get_type();

protected:
  bool eq(const Typ& other) const;
};

//********************************TUnit Header*******************************//

class TUnit : public Typ {
public:
  TUnit();
  std::string get_type();

protected:
  bool eq(const Typ& other) const;
};

//********************************TFunc Header*******************************//

class TFunc : public Typ {
private:
  Shared_Typ t1;
  Shared_Typ t2;

public:
  TFunc(Shared_Typ _t1, Shared_Typ _t2);
  std::string get_type();
  Shared_Typ get_first_subtype();
  Shared_Typ get_second_subtype();

protected:
  bool eq(const Typ& other) const;
};

//********************************TPair Header*******************************//

class TPair : public Typ {
private:
  Shared_Typ t1;
  Shared_Typ t2;

public:
  TPair(Shared_Typ _t1, Shared_Typ _t2);
  std::string get_type();
  Shared_Typ get_first_subtype();
  Shared_Typ get_second_subtype();

protected:
  bool eq(const Typ& other) const;
};

//********************************TList Header*******************************//

class TList : public Typ {
private:
  Shared_Typ t;

public:
  TList(Shared_Typ _t);
  std::string get_type();
  Shared_Typ get_first_subtype();

protected:
  bool eq(const Typ& other) const;
};

//********************************TRef Header*******************************//

class TRef : public Typ {
private:
  Shared_Typ t;

public:
  TRef(Shared_Typ _t);
  std::string get_type();
  Shared_Typ get_first_subtype();

protected:
  bool eq(const Typ& other) const;
};

#endif
