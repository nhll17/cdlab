#include<stdio.h>
#include<stdlib.h>
#define max 10
int n,eclosure[max][max],visited[max],adj[max][max];


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
    printf("enter the no of staates");
    scanf("%d",&n);
    int u,v,e;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adj[i][j]=0;
        }
    }
    printf("enter the no of epsilon transition");
    scanf("%d",&e);
    for(int i=0;i<e;i++){
    printf("enter the transitions");
    scanf("%d%d",&u,&v);
    adj[u][v]=1;
    }
    for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        visited[j]=0;

    }
    dfs(i,i);

    }
     for(int i=0;i<n;i++){
        printf("eclosure(%d)",i);
    for(int j=0;j<n;j++){
        if (eclosure[i][j]){
        printf("%d",j);
        }
    }
printf("\n");}

}