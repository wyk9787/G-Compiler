#include <stdio.h>
int f (int x);

int main (int a) {
int _g0comp = 1;
printf("%d\n", f(_g0comp));
 }

int f (int x) {
int _g2comp = x;
int _g3comp = 100;
int _g1comp = (_g2comp <= _g3comp);
int _g11comp;
if ( _g1comp) { int _g8comp = x;
int _g9comp = 1;
int _g7comp = (_g8comp + _g9comp);
int _g5comp = x;
int _g6comp = f(_g7comp);
int _g4comp = (_g5comp + _g6comp);
_g11comp = _g4comp;
 } else { int _g10comp = x;
_g11comp = _g10comp;
 }
return _g11comp;
 }


