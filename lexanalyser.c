#include <stdio.h>
#include <ctype.h>
#include <string.h>

// List of keywords (you can add more if needed)
char *keywords[] = {
    "int", "float", "if", "else", "while", "for", "return", "char", "double", "void"
};
int n_keywords = 10;

// Check if a string is a keyword
int isKeyword(char *str) {
    for (int i = 0; i < n_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// Check if a character is a delimiter
int isDelimiter(char ch) {
    return (ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' || ch == '[' || ch == ']');
}

int main() {
    char ch;
    printf("Enter code (Ctrl+D to stop):\n");

    while ((ch = getchar()) != EOF) {
        // Skip spaces, tabs, and newlines
        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        // Identifier or Keyword
        if (isalpha(ch) || ch == '_') {
            char buf[100];
            int i = 0;
            buf[i++] = ch;
            while ((ch = getchar()) != EOF && (isalnum(ch) || ch == '_')) {
                buf[i++] = ch;
            }
            buf[i] = '\0';

            if (isKeyword(buf))
                printf("KEYWORD: %s\n", buf);
            else
                printf("IDENTIFIER: %s\n", buf);

            if (ch != EOF) ungetc(ch, stdin);
        }
        // Number
        else if (isdigit(ch)) {
            char buf[100];
            int i = 0;
            buf[i++] = ch;
            while ((ch = getchar()) != EOF && isdigit(ch)) {
                buf[i++] = ch;
            }
            buf[i] = '\0';
            printf("NUMBER: %s\n", buf);

            if (ch != EOF) ungetc(ch, stdin);
        }
        // Delimiters
        else if (isDelimiter(ch)) {
            printf("DELIMITER: %c\n", ch);
        }
        // Operators (basic single-char)
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
                 ch == '=' || ch == '<' || ch == '>') {
            printf("OPERATOR: %c\n", ch);
        }
        else {
            printf("UNKNOWN: %c\n", ch);
        }
    }

    return 0;
}
