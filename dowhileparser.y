%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int yywrap();
int yyerror(char *s);
int yylex();
%}

%token DO WHILE lp rp sc id num op eq

%%

dowhile: DO lcb stmts rcb WHILE lp expr rp sc
;

exprs: expr
| id eq expr
;

expr: expra
| expr op expra
;

expra: id
| num
| lp expr rp
;

stmts: /*empty*/
| stmts stmt
;

stmt: exprs sc
| dowhile
;

%%

int yyerror(char *s){
    printf("%s",s);
    return 0;
}

int yywrap(){
    return 1;
}

int main(){
    printf("Enter the code: ");
    if(yyparse()==0){
        printf("Correct syntax\n");
    }
    else
        printf("Wrong syntax\n");
    return 0;
}
