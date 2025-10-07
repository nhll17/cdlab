%{
#include "y.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%
[a-zA-Z]+   { yylval.sval = strdup(yytext); return STRING; }
[\n\t ]+    { /* skip whitespace */ }
.           { /* ignore other chars */ }
%%

int yywrap() { return 1; }
