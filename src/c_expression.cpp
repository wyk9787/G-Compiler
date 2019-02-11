#include "c_expression.hpp"
#include <algorithm>

using namespace cexp;
using namespace ctyp;

/************* Print to C file *******************/

std::string string_of_blk(std::vector<Shared_Stmt> stmt_list) {
  std::string ret = "";
  for (int i = 0; i < stmt_list.size(); i++) {
    ret += stmt_list[i]->string_of_stmt() + "\n";
  }

  return ret;
}

std::string string_of_arg(c_arg_t arg) {
  return arg.second->string_of_typ() + " " + arg.first;
}

std::string string_of_fn(c_function_t func) {
  std::string arglist_str = "";
  for (int i = 0; i < func.arglist.size(); i++) {
    if (i != func.arglist.size() - 1)
      arglist_str += string_of_arg(func.arglist[i]) + ", ";
    else
      arglist_str += string_of_arg(func.arglist[i]);
  }

  return func.return_type->string_of_typ() + " " + func.name + " (" +
         arglist_str + ") {\n" + string_of_blk(func.stmt_list) + " }\n";
}

std::string string_of_fn_decl(c_function_t func) {
  std::string arglist_str = "";
  for (int i = 0; i < func.arglist.size(); i++) {
    if (i != func.arglist.size() - 1)
      arglist_str += string_of_arg(func.arglist[i]) + ", ";
    else
      arglist_str += string_of_arg(func.arglist[i]);
  }

  return func.return_type->string_of_typ() + " " + func.name + " (" +
         arglist_str + ");\n";
}

std::string string_of_prog(c_global_function_t functions) {
  std::string ret = "#include <stdio.h>\n";
  for (auto cur : functions) {
    if (cur.first == "main") continue;
    ret += string_of_fn_decl(cur.second) + "\n";
  }

  for (auto cur : functions) {
    ret += string_of_fn(cur.second) + "\n";
  }
  return ret;
}

/************** Convert Functions ****************/

c_arg_t conv_arg(arg_t arg) {
  return std::make_pair(arg.first, std::make_shared<TInt>());
}

c_function_t conv_fn(function_t func) {
  auto conv_exp = func.e->convert();

  arglist_t arglist = func.arglist;
  c_arglist_t c_arglist;
  c_arglist.resize(arglist.size());
  std::transform(arglist.begin(), arglist.end(), c_arglist.begin(), conv_arg);
  std::vector<Shared_Stmt> stmt_list(std::get<1>(conv_exp));
  if (func.name == "main") {
    stmt_list.push_back(std::make_shared<SPrint>(std::get<0>(conv_exp)));
  } else {
    stmt_list.push_back(std::make_shared<SRet>(std::get<0>(conv_exp)));
  }

  c_function_t ret = {.name = func.name,
                      .arglist = c_arglist,
                      .return_type = std::make_shared<TInt>(),
                      .stmt_list = stmt_list};

  return ret;
}

c_global_function_t conv_prog() {
  c_global_function_t ret;
  for (auto cur : global_functions) {
    ret.insert({cur.first, conv_fn(cur.second)});
  }
  return ret;
}

/***********************************************/

/******************************************************************************
                               EOperator Implementation
*******************************************************************************/

EOperator::EOperator(TokenKind _id, Shared_Exp _e1, Shared_Exp _e2)
    : id(_id), e1(_e1), e2(_e2) {}
std::string EOperator::string_of_exp() {
  return "(" + e1->string_of_exp() + " " + enum_string[id] + " " +
         e2->string_of_exp() + ")";
}

/******************************************************************************
                               ELit Implementation
*******************************************************************************/
ELit::ELit(int _data) : data(_data) {}
std::string ELit::string_of_exp() { return std::to_string(data); }

/******************************************************************************
                               EBool Implementation
*******************************************************************************/

EBool::EBool(bool _data) : data(_data) {}

std::string EBool::string_of_exp() { return std::to_string(data); }

/******************************************************************************
                               EVar Implementation
*******************************************************************************/

EVar::EVar(std::string _data) : data(_data) {}

std::string EVar::string_of_exp() { return data; }

std::string EVar::get_var() { return data; }

/******************************************************************************
                               EIf Implementation
*******************************************************************************/

EIf::EIf(Shared_Exp _e1, Shared_Exp _e2, Shared_Exp _e3)
    : e1(_e1), e2(_e2), e3(_e3) {}

std::string EIf::string_of_exp() {
  return "(" + e1->string_of_exp() + " ? " + e2->string_of_exp() + " : " +
         e3->string_of_exp() + ")";
}

/******************************************************************************
                               EApp Implementation
*******************************************************************************/

EApp::EApp(std::string _id, std::vector<Shared_Exp> _v) : id(_id), v(_v) {}

std::string EApp::string_of_exp() {
  std::string ret = id + "(";
  for (int i = 0; i < v.size(); i++) {
    if (i != v.size() - 1)
      ret += v[i]->string_of_exp() + ", ";
    else
      ret += v[i]->string_of_exp();
  }
  return ret + ")";
}

/******************************************************************************
                               EPair Implementation
*******************************************************************************/

EDot::EDot(std::string _struct_name, std::string _field_name)
    : struct_name(_struct_name), field_name(_field_name) {}

std::string EDot::string_of_exp() { return struct_name + "." + field_name; }
