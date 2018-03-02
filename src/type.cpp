#include <type.hpp>

void type_error(std::string expression, std::string expect, std::string actual) {
  std::cerr << "In " << expression << std::endl;
  std::cerr << "Expecting type " << expect << ", receiving type " << actual << std::endl;
  exit(1);
}

// bool operator ==(const Shared_Typ &first, const Shared_Typ &second){
//   if(typeid(first) == typeid(second)) {
//     std::cout << typeid(first.get()).name() << "\n";
//     std::cout << typeid(second.get()).name() << "\n";
//     return true;
//   } else {
//     std::cout << "false\n";
//     return false;
//   }
// }

TInt::TInt(){}

std::string TInt::get_type() {
  return "Int";
}

// bool TInt::operator ==(const Typ &other) const {
//   std::cout << "Enter TInt ==" << std::endl;
//   if (!Typ::operator==(other)) {
//     std::cout << "here2" << std::endl;
//     return false;
//   } else {
//     std::cout << "here3" << std::endl;
//     return true;
//   }
// }

TFloat::TFloat(){}

std::string TFloat::get_type() {
  return "Float";
}

// bool TFloat::operator ==(const Typ &other) const {
//   if (!Typ::operator==(other)) {
//     std::cout << "here4" << std::endl;
//     return false;
//   } else {
//     std::cout << "here5" << std::endl;
//     return true;
//   }
// }

TBool::TBool(){}

std::string TBool::get_type() {
  return "Boolean";
}

TFunc::TFunc(Shared_Typ _t1, Shared_Typ _t2) : t1(_t1), t2(_t2) {};

std::string TFunc::get_type() {
  return t1->get_type() + " -> " + t2->get_type();
}

Shared_Typ TFunc::get_first_subtype() {
  return t1;
}

Shared_Typ TFunc::get_second_subtype() {
  return t2;
}
