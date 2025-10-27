#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char icode[30][50];   // stores intermediate code lines
    char str[50], opr[10];
    int i = 0;

    printf("Enter the set of intermediate code (terminated by 'exit'):\n");

    // Read intermediate code lines
    do {
        scanf("%s", icode[i]);
    } while (strcmp(icode[i++], "exit") != 0);

    printf("\nTARGET CODE GENERATION");
    printf("\n-----------------------");

    i = 0;
    do {
        strcpy(str, icode[i]);

        // Handle IF condition: format → IFa<bGOTOL1
        if (strncmp(str, "IF", 2) == 0) {
            char op1 = str[2];
            char relop = str[3];
            char op2 = str[4];
            char label[10] = "";
            int k = 0;

            // Extract label name after "GOTO"
            for (int j = 8; str[j] != '\0'; j++) {
                label[k++] = str[j];
            }
            label[k] = '\0';

            printf("\nCMP %c, %c", op1, op2);
            switch (relop) {
                case '<': printf("\nJLT %s", label); break;
                case '>': printf("\nJGT %s", label); break;
                case '=': printf("\nJEQ %s", label); break;
                case '!': printf("\nJNE %s", label); break;
            }
        }

        // Handle GOTO statement: e.g. GOTO L2
        else if (strncmp(str, "GOTO", 4) == 0) {
            printf("\nJMP %s", str + 5);
        }

        // Handle label: e.g. L1:
        else if (strchr(str, ':')) {
            printf("\n%s", str);
        }

        // Handle assignments
        else {
            if (str[3] == '=') {
                // Simple assignment like T=a
                printf("\nMOV %c, %c", str[2], str[0]);
            } else {
                // Arithmetic operation like T=a+b
                switch (str[3]) {
                    case '+': strcpy(opr, "ADD"); break;
                    case '-': strcpy(opr, "SUB"); break;
                    case '*': strcpy(opr, "MUL"); break;
                    case '/': strcpy(opr, "DIV"); break;
                    default: strcpy(opr, ""); break;
                }

                printf("\nMOV %c, R%d", str[2], i);
                printf("\n%s %c, R%d", opr, str[4], i);
                printf("\nMOV R%d, %c", i, str[0]);
            }
        }

    } while (strcmp(icode[++i], "exit") != 0);

    printf("\n");
    return 0;
}
