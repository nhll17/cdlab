%{
#include "switch.tab.h"
#include <stdlib.h>
%}

%%

"switch"    { return SWITCH; }
"case"      { return CASE; }
"default"   { return DEFAULT; }
"break"     { return BREAK; }

\'[a-zA-Z0-9]\' { return CHAR; }  

[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
[0-9]+       { return NUM; }
":"          { return COLON; }
";"          { return SC; }
"("          { return LP; }
")"          { return RP; }
"{"          { return LPP; }
"}"          { return RPP; }
"="          { return EQ;}
[ \t\n]      { /* ignore whitespace */ }
.            { /* ignore unknowns */ }

%%

int yywrap(void) {
    return 1;
}
