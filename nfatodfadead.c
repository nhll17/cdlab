#include <stdio.h>
#define MAX 20

int nfa[MAX][MAX][MAX], dfa_states[MAX][MAX], dfa_trans[MAX][MAX], marked[MAX];
int n, m, dfa_count;
char symbols[MAX];

int sets_equal(int *a, int *b) {
    for (int i = 0; i < n; i++)
        if (a[i] != b[i]) return 0;
    return 1;
}

int find_state(int *set) {
    for (int i = 0; i < dfa_count; i++)
        if (sets_equal(dfa_states[i], set)) return i;
    return -1;
}

int add_state(int *set) {
    for (int i = 0; i < n; i++)
        dfa_states[dfa_count][i] = set[i];
    marked[dfa_count] = 0;
    return dfa_count++;
}

void print_state(int idx) {
    printf("{");
    int first = 1;
    for (int i = 0; i < n; i++)
        if (dfa_states[idx][i]) {
            if (!first) printf(",");
            printf("%d", i + 1);
            first = 0;
        }
    printf("}");
}

int empty(int *set) {
    for (int i = 0; i < n; i++)
        if (set[i]) return 0;
    return 1;
}

int main() {
    int t;
    printf("NFA states: "); scanf("%d", &n);
    printf("Input symbols: "); scanf("%d", &m);
    printf("Symbols: ");
    for (int i = 0; i < m; i++) scanf(" %c", &symbols[i]);

    
    for (int i = 0; i < MAX; i++) {
        marked[i] = 0;
        for (int j = 0; j < MAX; j++) {
            dfa_trans[i][j] = -1;
            dfa_states[i][j] = 0;
            for (int k = 0; k < MAX; k++)
                nfa[i][j][k] = 0;
        }
    }

    printf("Transitions count: "); scanf("%d", &t);
    printf("Enter transitions (from symbol to):\n");
    for (int i = 0; i < t; i++) {
        int f, to; char sym;
        scanf("%d %c %d", &f, &sym, &to);
        int si = -1;
        for (int j = 0; j < m; j++)
            if (symbols[j] == sym) si = j;
        if (si == -1) {
            printf("Invalid symbol '%c'!\n", sym);
            return 1;
        }
        nfa[f - 1][si][to - 1] = 1; 
    }


    int start[MAX] = {0};
    start[0] = 1;
    add_state(start);

   
    for (int i = 0; i < dfa_count; i++) {
        if (marked[i]) continue;
        marked[i] = 1;

        for (int c = 0; c < m; c++) {
            int next[MAX] = {0};
            for (int s = 0; s < n; s++)
                if (dfa_states[i][s])
                    for (int ns = 0; ns < n; ns++)
                        if (nfa[s][c][ns])
                            next[ns] = 1;

            int idx = -1;
            if (!empty(next)) idx = find_state(next);
            if (idx == -1 && !empty(next)) idx = add_state(next);
            dfa_trans[i][c] = idx;
        }
    }

    
    int dead[MAX] = {0}; // empty set
    int dead_idx = find_state(dead);
    if (dead_idx == -1) {
        dead_idx = add_state(dead);
        for (int c = 0; c < m; c++)
            dfa_trans[dead_idx][c] = dead_idx; 
    }

  
    for (int i = 0; i < dfa_count; i++) {
        for (int c = 0; c < m; c++) {
            if (dfa_trans[i][c] == -1)
                dfa_trans[i][c] = dead_idx;
        }
    }

   
    printf("\n--- DFA Transition Table ---\n");
    for (int i = 0; i < dfa_count; i++)
        for (int c = 0; c < m; c++) {
            printf("From state "); print_state(i);
            printf(" on '%c' -> ", symbols[c]);
            print_state(dfa_trans[i][c]);
            printf("\n");
        }

    return 0;
}
