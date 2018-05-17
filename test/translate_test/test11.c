#include <stdio.h>
int fact (int n);

int main (int a) {
int _g0comp = 4;
printf("%d\n", fact(_g0comp));
 }

int fact (int n) {
int _g2comp = n;
int _g3comp = 0;
int _g1comp = (_g2comp > _g3comp);
int _g11comp;
if ( _g1comp) { int _g8comp = n;
int _g9comp = 1;
int _g7comp = (_g8comp - _g9comp);
int _g5comp = n;
int _g6comp = fact(_g7comp);
int _g4comp = (_g5comp * _g6comp);
_g11comp = _g4comp;
 } else { int _g10comp = 1;
_g11comp = _g10comp;
 }
return _g11comp;
 }


