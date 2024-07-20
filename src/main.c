#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <limits.h>
#include "graph.h"
#include "heap.h"


#define INF INT_MAX

int main() {
    int V = 5;  // Número de vértices
    Graph* graph = createGraph(V);

    int x, y;
    for (int i = 0; i < 5; i++)
    {
        scanf("%d %d", &x, &y);
        addEdge(graph, x, y, 10);
    }
    

    //addPortal(graph, 0, 3);

    printf("Graph created successfully!\n");

    // Teste dijkstra
    int src = 0, dest = 3;
    int s = 20, k = 2;
    printf("\nRunning Dijkstra's algorithm from vertex %d to vertex %d with s=%d and k=%d:\n", src, dest, s, k);
    dijkstra(graph, src, dest, s, k);

    // Teste aStar (supondo que tenhamos coordenadas x e y dos vértices)
    //int xCoords[] = {0, 2, 4, 7, 9};
    //int yCoords[] = {0, 1, 3, 5, 8};
    //printf("\nRunning A* algorithm from vertex %d to vertex %d with s=%d and k=%d:\n", src, dest, s, k);
    //aStar(graph, src, dest, s, k, xCoords, yCoords);
    return 0;
}
