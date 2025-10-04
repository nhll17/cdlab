%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char name[40], sub[5];
%}

%%
[0-9a-zA-Z]+ {
    int len = strlen(yytext);
    int found = 0;
    for (int i = 0; i <= len - 4; i++) {
        int match = 1;
        for (int j = 0; j < 4; j++) {
            if (tolower(yytext[i + j]) != tolower(sub[j])) {
                match = 0;
                break;
            }
        }
        if (match) {
            found = 1;
            break;
        }
    }
    if (!found)
        printf(" substring\n", yytext);
    else
        printf("string\n", yytext);
}
[ \t\n]+ {}
%%

int yywrap(void) { return 1; }

int main() {
    printf("Enter your name: ");
    scanf("%s", name);
    strncpy(sub, name, 4);
    sub[4] = '\0';
    printf("Enter input: ");
    yylex();
    return 0;
}