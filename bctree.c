//Write a Program to implement Broadcast tree by taking subnet of hosts.

#include <stdio.h>
#define MAX 20
#define INF 9999
int main() {
 int n, i, j, u, v, min, total_cost = 0;
 int graph[MAX][MAX], visited[MAX] = {0}, edges = 0;
 printf("Enter the number of hosts (nodes): ");
 scanf("%d", &n);
 printf("Enter the adjacency matrix (cost 0 for self, %d for no direct link):\n", INF);
 for(i = 0; i < n; i++)
 for(j = 0; j < n; j++)
 scanf("%d", &graph[i][j]);
 visited[0] = 1; // Start from host 0
 printf("\nEdges in the broadcast (spanning) tree:\n");
 while(edges < n - 1) {
 min = INF;
 for(i = 0; i < n; i++) {
 if(visited[i]) {
 for(j = 0; j < n; j++) {
 if(!visited[j] && graph[i][j] < min && graph[i][j] != 0) {
 min = graph[i][j];
 u = i;
 v = j;
 }
 }
 }
 }
 printf("Host %d - Host %d : Cost = %d\n", u, v, min);
 total_cost += min;
 visited[v] = 1;
 edges++;
 }
 printf("Total cost of Broadcast Tree: %d\n", total_cost);
 return 0;
}
