#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define MAX_DFA 256 

int nfaTrans[MAX][MAX]; 
int dfaTrans[MAX_DFA][MAX];
int visited[MAX_DFA];
int numStates, numSymbols;
char symbols[MAX];

void printStateSet(int stateSet) {
    printf("{ ");
    for (int i = 0; i < numStates; i++) {
        if (stateSet & (1 << i)) printf("%d ", i);
    }
    printf("}");
}

// Find new DFA state (from set of NFA states)
int getNextState(int stateSet, int symbolIndex) {
    int nextSet = 0;
    for (int i = 0; i < numStates; i++) {
        if (stateSet & (1 << i)) {
            nextSet |= nfaTrans[i][symbolIndex];
        }
    }
    return nextSet;
}

// BFS through DFA states to build transition table
void convertNFAtoDFA(int startState) {
    int queue[MAX_DFA], front = 0, rear = 0;
    int dfaStateSet[MAX_DFA]; // bitmasks
    int stateCount = 0;

    // Initial DFA state is the singleton {startState}
    int startSet = (1 << startState);
    dfaStateSet[stateCount++] = startSet;
    visited[startSet] = 1;
    queue[rear++] = startSet;

    while (front < rear) {
        int currSet = queue[front++];
        for (int s = 0; s < numSymbols; s++) {
            int nextSet = getNextState(currSet, s);
            dfaTrans[currSet][s] = nextSet;

            if (!visited[nextSet] && nextSet != 0) {
                visited[nextSet] = 1;
                dfaStateSet[stateCount++] = nextSet;
                queue[rear++] = nextSet;
            }
        }
    }

    // Print DFA
    printf("\nDFA Transition Table:\n");
    for (int i = 0; i < stateCount; i++) {
        printf("From ");
        printStateSet(dfaStateSet[i]);
        printf(":\n");
        for (int s = 0; s < numSymbols; s++) {
            printf("  on '%c' -> ", symbols[s]);
            printStateSet(dfaTrans[dfaStateSet[i]][s]);
            printf("\n");
        }
    }
}

int main() {
    printf("Enter number of NFA states: ");
    scanf("%d", &numStates);

    printf("Enter number of input symbols: ");
    scanf("%d", &numSymbols);
    printf("Enter the symbols: ");
    for (int i = 0; i < numSymbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    // Initialize transitions
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            nfaTrans[i][j] = 0;

    int numTransitions;
    printf("Enter number of NFA transitions: ");
    scanf("%d", &numTransitions);
    printf("Enter transitions in format <from> <symbol> <to>:\n");
    for (int i = 0; i < numTransitions; i++) {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);
        for (int j = 0; j < numSymbols; j++) {
            if (symbols[j] == sym) {
                nfaTrans[from][j] |= (1 << to);
                break;
            }
        }
    }

    convertNFAtoDFA(0); // start state = 0
    return 0;
}
