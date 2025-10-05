%{
#include <stdio.h>
int yylex(void);
int yyerror(char *s);
%}


%token FOR ID NUM
%token OP
%token EQ
%token SC LP RP LPP RPP

%%

for : FOR LP exprs SC exprs SC exprs RP LPP stmts RPP
    | FOR LP exprs SC exprs SC exprs RP exprs SC
    ;

exprs    :ID EQ expr
	 | expr
	 ;

expr     : expra
         | expr OP expra
	
         ;
expra    : ID
	 | NUM
	 | LP expr RP
	 | ID DEC
	 | ID INC
	 ;


stmts : /* empty */
      | stmts stmt
      ;

stmt  : exprs SC
      | for
      ;

%%

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}

int main()
{
	printf("enter your code with EOF character:\n");
	if(yyparse()==0)
	{ 
		printf("Syntax correct\n");
	}
	else
	{
		printf("Invalid Syntax\n");
	}
}
