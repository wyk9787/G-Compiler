#include <type.hpp>

void type_error(std::string expression, std::string expect, std::string actual) {
  std::cerr << "In " << expression << std::endl;
  std::cerr << "Expecting type " << expect << ", receiving type " << actual << std::endl;
  exit(1);
}

bool operator==(const Typ &first, const Typ &second){
  return first.eq(second);
}

bool operator!=(const Typ &first, const Typ &second){
  return !first.eq(second);
}

//********************************TInt Implementaion****************************//

TInt::TInt(){}

std::string TInt::get_type() {
  return "Int";
}

bool TInt::eq(const Typ& other) const {
  const TInt *res = dynamic_cast<const TInt*>(&other);
  return res != nullptr;
}

//********************************TFloat Implementaion****************************//

TFloat::TFloat(){}

std::string TFloat::get_type() {
  return "Float";
}

bool TFloat::eq(const Typ& other) const {
  const TFloat *res = dynamic_cast<const TFloat*>(&other);
  return res != nullptr;
}

//********************************TBool Implementaion****************************//

TBool::TBool(){}

bool TBool::eq(const Typ& other) const {
  const TBool *res = dynamic_cast<const TBool*>(&other);
  return res != nullptr;
}

std::string TBool::get_type() {
  return "Boolean";
}

//********************************TUnit Implementaion****************************//

TUnit::TUnit(){}

std::string TUnit::get_type() {
  return "unit";
}

bool TUnit::eq(const Typ& other) const {
  const TUnit *res = dynamic_cast<const TUnit*>(&other);
  return res != nullptr;
}

//********************************TFunc Implementaion****************************//

TFunc::TFunc(Shared_Typ _t1, Shared_Typ _t2) : t1(_t1), t2(_t2) {};

bool TFunc::eq(const Typ& other) const {
  const TFunc *res = dynamic_cast<const TFunc*>(&other);
  return res != nullptr && *t1.get() == *const_cast<Typ&>(other).get_first_subtype().get() && *t2.get() == *const_cast<Typ&>(other).get_second_subtype().get();
}

std::string TFunc::get_type() {
  return t1->get_type() + " -> " + t2->get_type();
}

Shared_Typ TFunc::get_first_subtype() {
  return t1;
}

Shared_Typ TFunc::get_second_subtype() {
  return t2;
}

//********************************TPair Implementaion****************************//

TPair::TPair(Shared_Typ _t1, Shared_Typ _t2) : t1(_t1), t2(_t2) {};

bool TPair::eq(const Typ& other) const {
  const TPair *res = dynamic_cast<const TPair*>(&other);
  return res != nullptr && *t1.get() == *const_cast<Typ&>(other).get_first_subtype().get() && *t2.get() == *const_cast<Typ&>(other).get_second_subtype().get();
}

std::string TPair::get_type() {
  return t1->get_type() + " * " + t2->get_type();
}

Shared_Typ TPair::get_first_subtype() {
  return t1;
}

Shared_Typ TPair::get_second_subtype() {
  return t2;
}

//********************************TList Implementaion****************************//

TList::TList(Shared_Typ _t) : t(_t) {};

bool TList::eq(const Typ& other) const {
  const TList *res = dynamic_cast<const TList*>(&other);
  return res != nullptr && *t.get() == *const_cast<Typ&>(other).get_first_subtype().get();
}

std::string TList::get_type() {
  return "{" + t->get_type() + "}";
}

Shared_Typ TList::get_first_subtype() {
  return t;
}

//********************************TRef Implementaion****************************//

TRef::TRef(Shared_Typ _t) : t(_t) {};

bool TRef::eq(const Typ& other) const {
  const TRef *res = dynamic_cast<const TRef*>(&other);
  return res != nullptr && *t.get() == *const_cast<Typ&>(other).get_first_subtype().get();
}

std::string TRef::get_type() {
  return "<" + t->get_type() + ">";
}

Shared_Typ TRef::get_first_subtype() {
  return t;
}

//********************************TStruct Implementaion****************************//

TStruct::TStruct(struct_type_t _t_map) : t_map(_t_map) {}

std::string TStruct::get_type() {
  return "[-]";
}

struct_type_t TStruct::get_type_map() {
  return t_map;
}

bool TStruct::eq(const Typ& other) const {
  const TStruct *res = dynamic_cast<const TStruct*>(&other);
  return res != nullptr;
}
