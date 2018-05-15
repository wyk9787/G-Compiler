#ifndef STATEMENT_HPP
#define STATEMENT_HPP

using namespace cexp;

// Helper functions
std::string string_of_blk(std::vector<Shared_Stmt> stmt_list);

class Stmt {
  virtual std::string string_of_stmt() = 0;
};

class SDecl : Stmt{
private:
  std::string name;
  Shared_Typ t;
  Shared_Exp e;

public:
  SDecl(std::string _name, Shared_Typ _t, Shared_Exp _e);
  std::string string_of_stmt();
};

class SIf : Stmt{
private:
  Shared_Exp e;
  std::vector<Shared_Stmt> b1;
  std::vector<Shared_Stmt> b2;

public:
  SIf(Shared_Exp _e, std::vector<Shared_Stmt> _b1, std::vector<Shared_Stmt> b2);
  std::string string_of_stmt();
};

class SWhile : Stmt{
private:
  Shared_Exp e;
  std::vector<Shared_Stmt> b;

public:
  SWhile(Shared_Exp _e, std::vector<Shared_Stmt> _b);
  std::string string_of_stmt();
};

class SRet : Stmt{
private:
  Shared_Exp e;

public:
  SRet(Shared_Exp _e);
  std::string string_of_stmt();
};

class SPrint : Stmt{
private:
  Shared_Exp e;

public:
  SPrint(Shared_Exp _e);
  std::string string_of_stmt();
};


#endif
