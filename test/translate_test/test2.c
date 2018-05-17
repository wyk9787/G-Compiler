#include <stdio.h>
int prog (int a);

int main (int a) {
int _g1comp = 2;
int _g0comp = prog(_g1comp);
int _g4comp;
if ( _g0comp) { int _g2comp = 1;
_g4comp = _g2comp;
 } else { int _g3comp = 2;
_g4comp = _g3comp;
 }
printf("%d\n", _g4comp);
 }

int prog (int a) {
int _g7comp = 2;
int _g8comp = 4;
int _g6comp = (_g7comp <= _g8comp);
int _g13comp;
if ( _g6comp) { int _g9comp = 1;
_g13comp = _g9comp;
 } else { int _g11comp = 3;
int _g12comp = 4;
int _g10comp = (_g11comp > _g12comp);
_g13comp = _g10comp;
 }
int _g5comp = _g13comp;
int _g18comp;
if ( _g5comp) { int _g15comp = 1;
int _g16comp = a;
int _g14comp = (_g15comp <= _g16comp);
_g18comp = _g14comp;
 } else { int _g17comp = 0;
_g18comp = _g17comp;
 }
return _g18comp;
 }


