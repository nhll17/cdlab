%{
#include <stdio.h>
#include <string.h>

int yyerror(char *s);
int yylex();
char str[100];
%}

%union {
    char* sval;
}

%token <sval> STRING

%%

input: STRING {
    strcpy(stri, $1); 
    int len = strlen(str), flag = 1;
    for (int i = 0; i < len/2; i++)
        if (str[i] != str[len-i-1]) flag = 0;
    if (flag) printf("Palindrome\n");
    else printf("Not Palindrome\n");
};
%%
int yyerror(char *s){ return 0; }
int main(){
    printf("Enter a string: ");
    yyparse();
    return 0;
}
