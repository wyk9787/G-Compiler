#include "expression.hpp"
#include "interpreter.hpp"
#include <iostream>
#include <stdlib.h>

EOperator::EOperator(TokenKind t, std::shared_ptr<Exp> l,
                     std::shared_ptr<Exp> r)
    : id(t), e1(l), e2(r) {}

Result EOperator::evaluate() {
  Result e1_result = e1->evaluate();
  Result e2_result = e2->evaluate();
  Result result;
  if (e1_result.id == Int && e2_result.id == Int) {
    int e1_data = e1_result.int_data;
    int e2_data = e2_result.int_data;
    result.id = Int;
    switch (id) {
    case Plus:
      result.int_data = e1_data + e2_data;
      break;
    case Subtract:
      result.int_data = e1_data - e2_data;
      break;
    case Multiply:
      result.int_data = e1_data * e2_data;
      break;
    case Divide: {
      if (e2_data != 0) {
        result.int_data = e1_data / e2_data;
      } else if (e1_data == 0) { // e1_data = 0 and e2_data = 0
        result.id = NaN;
      } else {
        fprintf(stderr, "Fatal: Division by 0\n");
        exit(1);
      }
      break;
    }
    case Less_Than:
      result.id = Bool;
      result.bool_data = e1_data <= e2_data;
      break;
    default:
      fprintf(stderr, "This should never happen!\nDebug: EOp(1)\n");
      exit(1);
      break;
    }
  } else if (e1_result.id == Bool || e2_result.id == Bool) {
    fprintf(stderr, "Unexpected boolean value\n");
    exit(1);
  } else if (e1_result.id == NaN || e2_result.id == NaN) {
    result.id = NaN;
  } else if (e1_result.id == Float || e2_result.id == Float) {
    double e1_data;
    double e2_data;
    if (e1_result.id == Int) { // e1 is Int
      e1_data = (double)e1_result.int_data;
      e2_data = e2_result.float_data;
    } else if (e2_result.id == Int) { // e2 is Int
      e2_data = (double)e2_result.int_data;
      e1_data = e1_result.float_data;
    } else { // neither of them is Int
      e1_data = e1_result.float_data;
      e2_data = e2_result.float_data;
    }

    result.id = Float;
    switch (id) {
    case Plus:
      result.float_data = e1_data + e2_data;
      break;
    case Subtract:
      result.float_data = e1_data - e2_data;
      break;
    case Multiply:
      result.float_data = e1_data * e2_data;
      break;
    case Divide: {
      if (e2_data != 0) {
        result.float_data = e1_data / e2_data;
      } else if (e1_data == 0) { // e1_data = 0 and e2_data = 0
        result.id = NaN;
      } else {
        fprintf(stderr, "Division by 0\n");
        exit(1);
      }
      break;
    }
    case Less_Than:
      result.id = Bool;
      result.bool_data = e1_data <= e2_data;
      break;
    default:
      fprintf(stderr, "This should never happen!\nDebug: EOp(2)\n");
      exit(1);
    }
  } else {
    fprintf(stderr, "This should never happen!\nDebug: EOp(3)\n");
    exit(1);
  }
  return result;
}

std::string EOperator::string_of_exp() {
  return "(" + enum_string[id] + " " + e1->string_of_exp() + " " +
         e2->string_of_exp() + ")";
}

ELit::ELit(Token val) : data(val) {}

Result ELit::evaluate() {
  int id = data.id;
  Result result;
  if (id == True || id == False) {
    result.id = Bool;
    result.bool_data = data.bool_data;
  } else if (id == Num_Int) {
    result.id = Int;
    result.int_data = data.int_data;
  } else if (id == Num_Float) {
    result.id = Float;
    result.float_data = data.float_data;
  } else if (id == Lit_NaN) {
    result.id = NaN;
  } else {
    fprintf(stderr, "This should never happen!\nDebug: ELit");
    exit(1);
  }
  return result;
}

std::string ELit::string_of_exp() {
  int id = data.id;
  if (data.id == 6) {
    return std::to_string(data.int_data);
  } else if (data.id == 12) {
    return std::to_string(data.float_data);
  } else {
    return enum_string[id];
  }
}

EIf::EIf(std::shared_ptr<Exp> first, std::shared_ptr<Exp> second,
         std::shared_ptr<Exp> third)
    : e1(first), e2(second), e3(third) {}

Result EIf::evaluate() {
  Result e1_result = e1->evaluate();
  if (e1_result.id != Bool) {
    fprintf(stderr,
            "The first argument for the if statement should be a boolean.\n");
    exit(1);
  }
  if (e1_result.bool_data) {
    return e2->evaluate();
  }
  else {
    return e3->evaluate();
  }

}

std::string EIf::string_of_exp() {
  return "(if " + e1->string_of_exp() + " " + e2->string_of_exp() + " " +
         e3->string_of_exp() + ")";
}
