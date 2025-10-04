%{
#include <stdio.h>
#include <ctype.h>
int flag=0;
int yylex(void);
int yyerror(char *s);
int yywrap(void);
%}

%token LETTER NUMBER INVALID SPACE

%%
variable: LETTER valid 
	| LETTER     
	;
valid: LETTER valid
     | NUMBER valid
     | LETTER
     | NUMBER
     ;
%%

int yylex()
{
	int c=getchar();
	if(isalpha(c)) return LETTER;
	if(isdigit(c)) return NUMBER;
	else if(c==EOF) return 0;
	else if((c == '\n'))return 0;
	return INVALID;
	
	
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}

int yywrap() { return 1; }

int main() {
    printf("Enter variable: ");
    if(yyparse()==0)
    {
	printf("Valid variable");
    }
    else
    {
	printf("invalid variable");
    }
    return 0;
}