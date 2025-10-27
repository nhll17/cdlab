%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token SWITCH CASE DEFAULT BREAK ID NUM COLON SC LP RP LPP RPP EQ CHAR

%%
switch_stmt : SWITCH LP ID RP LPP case_list RPP
            ;

case_list   : case_list case_block
            | case_block
            ;

case_block  : CASE NUM COLON stmt_list 
            | CASE CHAR COLON stmt_list 
            | CASE NUM COLON stmt_list BREAK SC
            | DEFAULT COLON stmt_list
            ;

stmt_list   : stmt_list statement
            | statement
            ;

statement   : ID EQ NUM SC
            | BREAK SC
            | /* empty */
            ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main() {
    printf("Enter a switch statement:\n");
    if (yyparse() == 0)
        printf("Valid switch statement.\n");
    else
        printf("Invalid switch statement.\n");
    return 0;
}
