#include <stdio.h>
int prog (int b, int a);

int main (int a) {
int _g1comp = 3;
int _g2comp = 2;
int _g4comp = 2;
int _g5comp = 3;
int _g0comp = prog(_g1comp, _g2comp);
int _g3comp = prog(_g4comp, _g5comp);
printf("%d\n", (_g0comp + _g3comp));
 }

int prog (int b, int a) {
int _g7comp = a;
int _g8comp = b;
int _g6comp = (_g7comp >= _g8comp);
int _g17comp;
if ( _g6comp) { int _g10comp = 3;
int _g11comp = 2;
int _g9comp = (_g10comp * _g11comp);
_g17comp = _g9comp;
 } else { int _g15comp = 11;
int _g16comp = 7;
int _g13comp = 5;
int _g14comp = (_g15comp / _g16comp);
int _g12comp = (_g13comp + _g14comp);
_g17comp = _g12comp;
 }
return _g17comp;
 }


