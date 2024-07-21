#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <limits.h>
#include "graph.h"
#include "heap.h"


#define INF INT_MAX

int main() {

    int n, m, p;//n: numero de vertices, m numero de trilhas, p numero de portais
    scanf("%d %d %d", &n, &m, &p);
    Graph* graph = createGraph(n);
    int x, y;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &x, &y);
        addPosition(graph,x,y,i);
    }
    int u, v;
    for (int j = 0; j < m; j++)
    {
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }
    int a, b;
    for (int k = 0; k < p; k++)
    {
        scanf("%d %d", &a, &b);
        addPortal(graph, a, b);
    }

    int s;//quantidade de energia que pode ser usada
    int q;//numero de portais que podem ser usados
    
    scanf("%d %d", &s, &q);


    printf("Graph created successfully!\n");

    // Teste dijkstra
    int src = 0, dest = n-1;
    printf("\nRunning Dijkstra's algorithm from vertex %d to vertex %d with s=%d and q=%d:\n", src, dest, s, q);
    dijkstra(graph, src, dest, s, q);

    return 0;
}