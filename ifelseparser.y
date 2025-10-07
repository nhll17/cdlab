%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int yywrap();
int yyerror(char *s);
int yylex();
%}

%token IF ELSE lp rp lcb rcb id sc num op eq

%%

ifstmt: IF lp expr rp lcb stmts rcb
| IF lp expr rp lcb stmts rcb ELSE lcb stmts rcb
| IF lp expr rp lcb stmts rcb ELSE ifstmt
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
| ifstmt
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
