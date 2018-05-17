#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "c_expression.hpp"
#include "c_type.hpp"
#include <string>
#include <vector>

class Stmt {
public:
  virtual std::string string_of_stmt() = 0;
};

class SDecl : public Stmt {
private:
  std::string name;
  ctyp::Shared_Typ t;
  cexp::Shared_Exp e;

public:
  SDecl(std::string _name, ctyp::Shared_Typ _t, cexp::Shared_Exp _e);
  std::string string_of_stmt();
};

class SIf : public Stmt {
private:
  cexp::Shared_Exp e;
  std::vector<Shared_Stmt> b1;
  std::vector<Shared_Stmt> b2;

public:
  SIf(cexp::Shared_Exp _e, std::vector<Shared_Stmt> _b1,
      std::vector<Shared_Stmt> b2);
  std::string string_of_stmt();
};

class SWhile : public Stmt {
private:
  cexp::Shared_Exp e;
  std::vector<Shared_Stmt> b;

public:
  SWhile(cexp::Shared_Exp _e, std::vector<Shared_Stmt> _b);
  std::string string_of_stmt();
};

class SRet : public Stmt {
private:
  cexp::Shared_Exp e;

public:
  SRet(cexp::Shared_Exp _e);
  std::string string_of_stmt();
};

class SPrint : public Stmt {
private:
  cexp::Shared_Exp e;

public:
  SPrint(cexp::Shared_Exp _e);
  std::string string_of_stmt();
};

class SAssign : public Stmt{
private:
  std::string name;
  cexp::Shared_Exp e;

public:
  SAssign(std::string _name, cexp::Shared_Exp _e);
  std::string string_of_stmt();
};

class SDef : public Stmt {
private:
  ctyp::Shared_Typ t;
  std::string name;

public:
  SDef(ctyp::Shared_Typ _t, std::string _name);
  std::string string_of_stmt();
};

class SStruct : public Stmt {
private:
  std::string name;
  Shared_Stmt s1;
  Shared_Stmt s2;

public:
  SStruct(std::string _name, Shared_Stmt _s1, Shared_Stmt _s2);
  std::string string_of_stmt();
};

#endif
