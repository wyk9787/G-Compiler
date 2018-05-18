#include <stdio.h>
int main (int a) {
int _g5comp = 3;
int _g6comp = 4;
int _g2comp = 1;
int _g3comp = 2;
int _g1comp = (_g2comp + _g3comp);
int _g4comp = (_g5comp + _g6comp);
struct _g7comp {
int first;
int second;
};
struct _g7comp _g8comp;
_g8comp.first = _g1comp;
_g8comp.second = _g4comp;
int _g15comp = 3;
int _g16comp = 8;
int _g12comp = 4;
int _g13comp = 2;
int _g11comp = (_g12comp - _g13comp);
int _g14comp = (_g15comp * _g16comp);
struct _g17comp {
int first;
int second;
};
struct _g17comp _g18comp;
_g18comp.first = _g11comp;
_g18comp.second = _g14comp;
int _g0comp = _g8comp.first;
int _g10comp = _g18comp.second;
printf("%d\n", (_g0comp + _g10comp));
 }


