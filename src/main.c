#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <limits.h>
#include <time.h>
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
    clock_t start = clock();
    dijkstra(graph, src, dest, s, q);
    clock_t end = clock();
    double time_spent_dijkstra = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Dijkstra execution time: %f seconds\n", time_spent_dijkstra);
    printf("\n\n");
    printf("Running A* algorithm from vertex %d to vertex %d with s=%f q = %d :\n", src, dest, s, q);
    start = clock();
    aStar(graph, src, dest, s, q);
    end = clock();
    double time_spent_astar = (double)(end - start) / CLOCKS_PER_SEC;
    printf("A* execution time: %f seconds\n", time_spent_astar);
    return 0;
}