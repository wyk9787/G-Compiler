#include <stdio.h>
int max2 (int y, int x);

int main (int a) {
int _g0comp = 4;
int _g1comp = 3;
printf("%d\n", max2(_g0comp, _g1comp));
 }

int max2 (int y, int x) {
int _g3comp = x;
int _g4comp = y;
int _g2comp = (_g3comp > _g4comp);
int _g7comp;
if ( _g2comp) { int _g5comp = x;
_g7comp = _g5comp;
 } else { int _g6comp = y;
_g7comp = _g6comp;
 }
return _g7comp;
 }


