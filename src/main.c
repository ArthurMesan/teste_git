#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"


int main() {
    int V = 5;
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 20);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 2, 3, 10);
    addEdge(graph, 4, 3, 30);

    addPortal(graph, 0, 3);

    int xCoords[] = {0, 1, 2, 3, 4}; // Coordenadas X das clareiras
    int yCoords[] = {0, 1, 2, 3, 4}; // Coordenadas Y das clareiras

    int s = 40; // Energia disponível
    int k = 1;  // Máximo de portais

    printf("Dijkstra Modified:\n");
    dijkstra(graph, 0, 3, s, k);

    printf("A* Modified:\n");
    aStar(graph, 0, 3, s, k, xCoords, yCoords);


    freeGraph(graph);
    
    return 0;
}
