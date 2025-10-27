#include <stdio.h>

char input[100];
int pos = 0;

// Function declarations
int E();
int E_prime();
int T();
int T_prime();
int F();

int main() {
    printf("Enter an expression (use 'i' for identifiers):\n");
    scanf("%s", input);

    if (E() && input[pos] == '\0')
        printf("Expression is valid.\n");
    else
        printf("Expression is invalid.\n");

    return 0;
}

// E → T E'
int E() {
    if (T())
        if (E_prime())
            return 1;
    return 0;
}

// E' → + T E' | ε
int E_prime() {
    if (input[pos] == '+') {
        pos++;           // consume '+'
        if (T())
            if (E_prime())
                return 1;
        return 0;       // fail if T or E' fails
    }
    return 1;           // epsilon
}

// T → F T'
int T() {
    if (F())
        if (T_prime())
            return 1;
    return 0;
}

// T' → * F T' | ε
int T_prime() {
    if (input[pos] == '*') {
        pos++;           // consume '*'
        if (F())
            if (T_prime())
                return 1;
        return 0;       // fail
    }
    return 1;           // epsilon
}

// F → ( E ) | i
int F() {
    if (input[pos] == '(') {
        pos++;           // consume '('
        if (E()) {
            if (input[pos] == ')') {
                pos++;   // consume ')'
                return 1;
            } else
                return 0; // missing ')'
        } else
            return 0;     // invalid E inside ()
    } else if (input[pos] == 'i') {
        pos++;           // consume identifiercdc
        return 1;
    }
    return 0;             // invalid token
}
