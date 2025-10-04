#include<stdio.h>
#include<stdlib.h>
#define max 10

int n, m, adj[max][max], eclosure[max][max], visited[max];
int sigma[max][max][max]; // [state][input_index][state]
int nfa[max][max][max];   // Result transitions

void dfs(int state, int s){
    if (visited[state]) return;
    visited[state]=1;
    eclosure[s][state]=1;
    for (int i=0;i<n;i++){
        if (adj[state][i]==1){
            dfs(i,s);
        }
    }
}
int main(){
    int e, u, v, t;
    char symbols[max];

    printf("Enter the number of states: ");
    scanf("%d",&n);

    printf("Enter the number of input symbols (excluding epsilon): ");
    scanf("%d",&m);
    printf("Enter input symbols (space separated): ");
    for(int i=0;i<m;i++) {
        scanf(" %c", &symbols[i]);
    }

    // initialization
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            adj[i][j]=eclosure[i][j]=visited[j]=0;

    printf("Enter the number of epsilon transitions: ");
    scanf("%d",&e);
    printf("Enter epsilon transitions (u v):\n");
    for(int i=0;i<e;i++){
        scanf("%d%d",&u,&v);
        adj[u-1][v-1]=1; // 0-based
    }

    // epsilon closures
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) visited[j]=0;
        dfs(i,i);
    }

    // input transitions
    printf("Enter the number of non-epsilon transitions: ");
    scanf("%d",&t);
    printf("Enter transitions (u symbol v):\n");
    for(int i=0;i<t;i++) {
        char sy;
        scanf("%d %c %d", &u, &sy, &v);
        int sym = -1;
        for(int k=0;k<m;k++) {
            if(symbols[k]==sy) { sym=k; break; }
        }
        if(sym!=-1)
            sigma[u-1][sym][v-1]=1;
    }

    // NFA construction
    for(int s=0;s<n;s++) {
        for(int c=0;c<m;c++) {
            for(int t=0;t<n;t++) {
                if(eclosure[s][t]) {
                    for(int u=0;u<n;u++) {
                        if(sigma[t][c][u]) {
                            for(int v=0;v<n;v++) {
                                if(eclosure[u][v])
                                    nfa[s][c][v]=1;
                            }
                        }
                    }
                }
            }
        }
    }
printf("\nEpsilon-closure sets representing each NFA state:\n");
for (int s = 0; s < n; s++) {
    printf("State %d is composed of epsilon-NFA states: ", s + 1);
    for (int st = 0; st < n; st++) {
        if (eclosure[s][st]) {
            printf("%d ", st + 1);
        }
    }
    printf("\n");
}

    // Print transitions
    printf("NFA Transition Table (state, symbol, reachable states):\n");
    for(int s=0;s<n;s++) {
        for(int c=0;c<m;c++) {
            printf("From state %d on '%c': ", s+1, symbols[c]);
            int found=0;
            for(int v=0;v<n;v++)
                if(nfa[s][c][v]) { printf("%d ", v+1); found=1; }
            if(!found) printf("None");
            printf("\n");
        }
    }
    return 0;
}
