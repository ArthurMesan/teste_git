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
    double x, y;
    for (int i = 0; i < n; i++)
    {
        scanf("%le %le", &x, &y);
        addVertexPosition(graph,i,x,y);
    }
    int u, v;
    for (int j = 0; j < m; j++)
    {
        scanf("%d %d", &u, &v);
        addEdgeWithDistance(graph, u, v);
    }
    int a, b;
    for (int k = 0; k < p; k++)
    {
        scanf("%d %d", &a, &b);
        addPortal(graph, a, b);
    }

    double s;//quantidade de energia que pode ser usada
    int q;//numero de portais que podem ser usados
    
    scanf("%le %d", &s,&q);


    printf("Graph created successfully!\n");
    int src = 0, dest = n-1;
    printf("Running Dijkstra's algorithm from vertex %d to vertex %d with s=%f q = %d :\n", src, dest, s, q);
    dijkstra(graph, 0, dest, s, q);
    printf("\n\n");
    printf("Running A* algorithm from vertex %d to vertex %d with s=%f q = %d :\n", src, dest, s, q);
    aStar(graph, 0, dest, s, q);
    return 0;
}