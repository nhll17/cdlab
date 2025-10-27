#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char firstSet[MAX][MAX];
char followSet[MAX][MAX];
int n;

// Function declarations
void findFirst(char*, char);
void findFollow(char*, char);
int isNonTerminal(char);
void addUnique(char*, char);
void mergeSets(char*, char*);

int main() {
    int i;
    char ch;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use # for epsilon, no spaces)\n");
    for (i = 0; i < n; i++) {
        scanf("%s", production[i]);
    }

    for (i = 0; i < n; i++) {
        ch = production[i][0];
        findFirst(firstSet[i], ch);
    }

    for (i = 0; i < n; i++) {
        ch = production[i][0];
        findFollow(followSet[i], ch);
    }

    printf("\n---- FIRST and FOLLOW sets ----\n");
    for (i = 0; i < n; i++) {
        printf("FIRST(%c) = { %s }\n", production[i][0], firstSet[i]);
        printf("FOLLOW(%c) = { %s }\n\n", production[i][0], followSet[i]);
    }

    return 0;
}

// Check if symbol is Non-Terminal
int isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

// Add element uniquely
void addUnique(char* set, char c) {
    if (strchr(set, c) == NULL) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

// Merge two sets (unique)
void mergeSets(char* dest, char* src) {
    for (int i = 0; src[i] != '\0'; i++) {
        addUnique(dest, src[i]);
    }
}

// Find FIRST set
void findFirst(char* result, char c) {
    result[0] = '\0';

    if (!isNonTerminal(c)) { // terminal
        addUnique(result, c);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (production[i][0] == c) {
            // RHS symbol
            char symbol = production[i][2];

            if (symbol == '#') {
                addUnique(result, '#');
            } else if (!isNonTerminal(symbol)) {
                addUnique(result, symbol);
            } else {
                char temp[MAX] = "";
                findFirst(temp, symbol);
                mergeSets(result, temp);
            }
        }
    }
}

// Find FOLLOW set
void findFollow(char* result, char c) {
    result[0] = '\0';

    // Rule 1: Add '$' to start symbol's FOLLOW
    if (production[0][0] == c) addUnique(result, '$');

    for (int i = 0; i < n; i++) {
        char *rhs = strchr(production[i], '=');
        rhs++;

        for (int j = 0; j < strlen(rhs); j++) {
            if (rhs[j] == c) {
                // Case 1: followed by another symbol
                if (rhs[j + 1] != '\0') {
                    char next = rhs[j + 1];

                    if (!isNonTerminal(next)) {
                        addUnique(result, next);
                    } else {
                        char temp[MAX] = "";
                        findFirst(temp, next);
                        for (int k = 0; temp[k] != '\0'; k++) {
                            if (temp[k] != '#')
                                addUnique(result, temp[k]);
                        }

                        // If epsilon present, also add FOLLOW(LHS)
                        if (strchr(temp, '#') != NULL) {
                            char tempFollow[MAX] = "";
                            findFollow(tempFollow, production[i][0]);
                            mergeSets(result, tempFollow);
                        }
                    }
                }

                // Case 2: symbol at the end of production
                if (rhs[j + 1] == '\0' && c != production[i][0]) {
                    char tempFollow[MAX] = "";
                    findFollow(tempFollow, production[i][0]);
                    mergeSets(result, tempFollow);
                }
            }
        }
    }
}
