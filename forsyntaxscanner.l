%{
#include "forsyntaxparser.tab.h"
#include <stdlib.h>
%}

%%
"for"  { return FOR; }
[a-zA-Z_][a-zA-Z0-9_]* {return ID;}
[0-9]+ {return NUM;}
"="    { return EQ; }
"("    {return LP;}
")"    {return RP;}
[-+*/><]   {return OP;}
[ \t\n] {};
";"    {return SC;}
"{"    {return LPP;}
"}"    {return RPP;}


%%
int yywrap(void) {
    return 1;
}