#include <stdio.h>
int prog(int a);

int main(int a) {
  printf("a: %d\n", a);
  int _g0comp = 3;
  printf("%d\n", prog(_g0comp));
}

int prog(int a) {
  int _g2comp = 0;
  int _g5comp;
  if (_g2comp) {
    int _g3comp = 1;
    _g5comp = _g3comp;
  } else {
    int _g4comp = 0;
    _g5comp = _g4comp;
  }
  int _g1comp = _g5comp;
  int _g22comp;
  if (_g1comp) {
    int _g7comp = 10;
    int _g8comp = 0;
    int _g6comp = (_g7comp + _g8comp);
    _g22comp = _g6comp;
  } else {
    int _g10comp = 0;
    int _g21comp;
    if (_g10comp) {
      int _g14comp = 2;
      int _g15comp = 2;
      int _g12comp = 3;
      int _g13comp = (_g14comp / _g15comp);
      int _g11comp = (_g12comp + _g13comp);
      _g21comp = _g11comp;
    } else {
      int _g18comp = 3;
      int _g19comp = 0;
      int _g17comp = (_g18comp * _g19comp);
      int _g20comp = a;
      int _g16comp = (_g17comp + _g20comp);
      _g21comp = _g16comp;
    }
    int _g9comp = _g21comp;
    _g22comp = _g9comp;
  }
  return _g22comp;
}
