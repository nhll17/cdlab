%{
#include <stdio.h>
int fval=0;
int yylex(void);
int yyerror(char *s);
%}

%union {
     int  ival;      
}


%token <ival> NUMBER
%token PLUS MINUS MULTIPLICATION DIVISION LBRACKET RBRACKET
%type  <ival> A B C 
%%
A: A PLUS B {$$=$1+$3;fval=$1+$3;}
 | B        {$$=$1;fval=$1;}
 | A MINUS B {$$=$1-$3;fval=$1-$3;}
 ;

B: B MULTIPLICATION C {$$=$1*$3;}
 | B DIVISION C {$$=$1/$3;}
 | C {$$=$1;}
 ;

C: NUMBER {$$=$1;}
 | LBRACKET A RBRACKET {$$=$2;}
 ;
%%


int main() {
    printf("Enter expression: ");
    if (yyparse() == 0) {
        printf("Result = %d\n", fval);
    }
    return 0;
}

int yywrap(void) {
    return 1;
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}