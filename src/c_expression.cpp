#include "c_expression.hpp"
#include <algorithm>

using namespace cexp;
using namespace ctyp;

/************* Print to C file *******************/

std::string string_of_blk(std::vector<Shared_Stmt> stmt_list, std::string ret) {
  if(stmt_list.size() == 0) {
    return ret;
  } else {
    // TODO: Watch out local variable here
    Shared_Stmt first = stmt_list[0];
    stmt_list.erase(stmt_list.begin());
    return string_of_blk(stmt_list, ret + " " + first->string_of_stmt());
  }
}

std::string string_of_arg(c_arg_t arg) {
  return arg.first + " " + arg.second->string_of_typ();
}

std::string string_of_fn(c_function_t func) {
  std::string arglist_str = "";
  for(int i = 0; i < func.arglist.size(); i++) {
    if(i != func.arglist.size()-1)
      str += string_of_arg(func.arglist[i]) + ", ";
    else
      str += string_of_arg(func.arglist[i]);
  }

  std::transform(arglist.begin(), arglist.end(), )
  return func.return_type->string_of_typ() + " " + func.name + " " + arglist_str + " { " + string_of_blk(func.stmt_list) + " }";
}

std::string string_of_prog(c_global_function_t functions) {
  std::string ret = "#include <stdio.h>\n";
  for(int i = 0; i < functions.size(); i++) {
    ret += string_of_fn(functions);
  }
  return ret;
}


/************** Convert Functions ****************/

c_arg_t conv_arg(arg_t arg) {
  return {arg.first, std::make_shared<TInt>()};
}

c_function_t conv_fn(function_t func) {
  auto conv_exp = func.e->convert();

  arglist_t arglist = func.arglist;
  c_arglist_t c_arglist;
  c_arglist.resize(arglist.size());
  std::transform(arglist.begin(), arglist.end(), c_arglist.begin(), conv_arg);
  std::vector<Shared_Stmt> stmt_list(std::get<1>(conv_exp));
  if(func.name == "main") {
    stmt_list.push_back(std::make_shared<SPrint>(std::get<0>(conv_exp)));
  } else {
    stmt_list.push_back(std::make_shared<SRet>(std::get<0>(conv_exp)));
  }

  c_function_t ret = {
    .name = func.name,
    .arglist = c_arglist,
    .return_type = std::make_shared<TInt>(),
    .stmt_list = stmt_list
  };

  return ret;
}

c_global_function_t conv_prog() {
  c_global_function_t ret;
  for(auto cur : global_functions) {
    ret.insert({cur.first, conv_fn(cur.second)});
  }
  return ret;
}

/***********************************************/

/******************************************************************************
                               Exp Implementation
*******************************************************************************/

class Exp {
public:
  virtual std::string string_of_exp() = 0;
  virtual ~Exp(){};
};

/******************************************************************************
                               EOperator Implementation
*******************************************************************************/

class EOperator : public Exp {
  EOperator(TokenKind _id, Shared_Exp _e1, Shared_Exp _e2) : id(_id), e1(_e1), e2(_e2) {}
  std::string string_of_exp() {
    return "(" + e1->string_of_exp() + " " + enum_string[id] + " " + e2->string_of_exp() + ")"
  }
};

/******************************************************************************
                               ELit Implementation
*******************************************************************************/

class ELit : public Exp {
private:
  int data;

public:
  ELit(int _data) : data(_data);
  std::string string_of_exp() {
    return std::to_string(data);
  }
};

/******************************************************************************
                               EBool Implementation
*******************************************************************************/

class EBool : public Exp {
public:
  EBool(bool _data) : data(_data) {}

  std::string string_of_exp() {
    return std::to_string(data);
  }
};

/******************************************************************************
                               EVar Implementation
*******************************************************************************/

class EVar : public Exp {
public:
  EVar(std::string _data) : data(_data) {}

  std::string string_of_exp() { return data; }
};


/******************************************************************************
                               EIf Implementation
*******************************************************************************/

class EIf : public Exp {
public:
  EIf(Shared_Exp _e1, Shared_Exp _e2, Shared_Exp _e3) : e1(_e1), e2(_e2), e3(_e3) {}

  std::string string_of_exp() {
    return "(" + e1->string_of_exp() + " ? " + e2->string_of_exp() + " : " + e3->string_of_exp() + ")";
  }
};


/******************************************************************************
                               EApp Implementation
*******************************************************************************/

class EApp : public Exp {
private:
  std::string id;
  std::vector<Shared_Exp> v;

public:
  EApp(std::string _id, std::vector<Shared_Exp> _v) : id(_id), v(_v) {}

  std::string string_of_exp() {
    std::string ret = id + "(";
    for(int i = 0; i < v.size(); i++) {
      if(i != v.size() - 1)
        ret += v[i]->string_of_exp() + ", ";
      else
        ret += v[i]->string_of_exp();
    }
    return ret + ")"
  }
};
