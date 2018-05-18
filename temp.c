#include <stdio.h>
int pair_func (int x);

int main (int a) {
int _g1comp = 3;
int _g2comp = 4;
struct _g3comp {
int first;
int second;
};
struct _g3comp _g4comp;
_g4comp.first = _g1comp;
_g4comp.second = _g2comp;
int _g0comp = _g4comp;
printf("%d\n", pair_func(_g0comp));
 }

int pair_func (int x) {
int _g6comp = x.first;
int _g8comp = x.second;
int _g5comp = (_g6comp > _g8comp);
int _g20comp;
if ( _g5comp) { int _g11comp = x.first;
int _g13comp = x.second;
int _g10comp = (_g11comp - _g13comp);
_g20comp = _g10comp;
 } else { int _g16comp = x.first;
int _g18comp = x.second;
int _g15comp = (_g16comp + _g18comp);
_g20comp = _g15comp;
 }
return _g20comp;
 }


