
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int main() {
    int n, m;
    printf("Enter number of states in DFA: ");
    scanf("%d", &n);
    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    int trans[MAX][MAX];
    printf("Enter transition table (state x symbol -> next state):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &trans[i][j]);

    int final[MAX], fcount;
    printf("Enter number of final states: ");
    scanf("%d", &fcount);

    for (int i = 0; i < n; i++) final[i] = 0;
    printf("Enter final states: ");
    for (int i = 0; i < fcount; i++) {
        int x; scanf("%d", &x);
        final[x] = 1;
    }

    int distinguish[MAX][MAX] = {0};
    // mark final/nonfinal pairs
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (final[i] != final[j])
                distinguish[i][j] = 1;
        }
    }

    // refinement
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!distinguish[i][j]) {
                    for (int s = 0; s < m; s++) {
                        int p = trans[i][s], q = trans[j][s];
                        if (p > q) { int tmp = p; p = q; q = tmp; }
                        if (distinguish[p][q]) {
                            distinguish[i][j] = 1;
                            changed = 1;
                        }
                    }
                }
            }
        }
    }

    printf("\nEquivalent states:\n");
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!distinguish[i][j])
                printf("State %d and %d are equivalent\n", i, j);
        }
    }

    return 0;
}
