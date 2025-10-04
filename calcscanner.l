%{
#include "calculateparser.tab.h"
#include <stdlib.h>
%}

%%
[1-9][0-9]* {yylval.ival=atoi(yytext);return NUMBER;}
[0] {yylval.ival=atoi(yytext);return NUMBER;}
[+] {return PLUS;}
[/] {return DIVISION;}
[*] {return MULTIPLICATION;}
[-] {return MINUS;}
[(] {return LBRACKET;}
[)] {return RBRACKET;}
[\n] {return 0;}
[ \t]   {};

%%