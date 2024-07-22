#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include "graph.h"
#include "heap.h"

#define INF DBL_MAX

// Função para criar um grafo com V vértices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adjMatrix = (double**)malloc(V * sizeof(double*));
    graph->vertices = (Vertex*)malloc(V * sizeof(Vertex));
    
    for (int i = 0; i < V; i++) {
        graph->adjMatrix[i] = (double*)malloc(V * sizeof(double));
        for (int j = 0; j < V; j++) {
            graph->adjMatrix[i][j] = (i == j) ? 0 : INF; // Inicializar com INF para representar ausência de arestas
        }
        graph->vertices[i].x = 0.0;
        graph->vertices[i].y = 0.0;
    }
    
    return graph;
}

// Função para liberar a memória de um grafo
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph->vertices);
    free(graph);
}

// Função para adicionar um vértice com posição (x, y)
void addVertexPosition(Graph* graph, int vertex, double x, double y) {
    if (vertex >= 0 && vertex < graph->V) {
        graph->vertices[vertex].x = x;
        graph->vertices[vertex].y = y;
    }
}

// Função para obter a posição de um vértice
void getVertexPosition(Graph* graph, int vertex, double* x, double* y) {
    if (vertex >= 0 && vertex < graph->V) {
        *x = graph->vertices[vertex].x;
        *y = graph->vertices[vertex].y;
    }
}

// Função para calcular a distância euclidiana entre dois vértices
double euclideanDistance(Graph* graph, int u, int v) {
    double x1 = graph->vertices[u].x;
    double y1 = graph->vertices[u].y;
    double x2 = graph->vertices[v].x;
    double y2 = graph->vertices[v].y;
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Função para adicionar uma aresta ao grafo
void addEdge(Graph* graph, int src, int dest, double weight) {
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight; // Se o grafo for não direcionado
}

// Função para adicionar uma aresta com peso baseado na distância euclidiana
void addEdgeWithDistance(Graph* graph, int src, int dest) {
    double weight = euclideanDistance(graph, src, dest);
    addEdge(graph, src, dest, weight);
}

// Função para adicionar um portal ao grafo (considerando peso zero)
void addPortal(Graph* graph, int src, int dest) {
    if (src >= graph->V || dest >= graph->V || src < 0 || dest < 0) {
        fprintf(stderr, "Invalid edge\n");
        return;
    }

    graph->adjMatrix[src][dest] = 0;
    graph->adjMatrix[dest][src] = 0; // Se o grafo for não direcionado
}

void dijkstra(Graph* graph, int src, int dest, double s, int k) {
    int V = graph->V;
    double dist[V];
    int portalsUsed[V];
    bool visited[V];
    MinHeap* minHeap = createMinHeap(V);

    if (!minHeap) {
        fprintf(stderr, "Failed to create MinHeap\n");
        return;
    }

    // Inicialização
    for (int i = 0; i < V; ++i) {
        dist[i] = INF;
        portalsUsed[i] = 0;
        visited[i] = false;
        minHeap->array[i] = newMinHeapNode(i, dist[i], 0);
        minHeap->pos[i] = i;
    }

    minHeap->array[src] = newMinHeapNode(src, 0, 0);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src], portalsUsed[src]);
    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        if (!minHeapNode) {
            fprintf(stderr, "Failed to extract min node. Heap might be empty.\n");
            break;
        }
        int u = minHeapNode->v;
        free(minHeapNode);

        if (u == dest) {
            printf("Found path with distance %f and %d portals used\n", dist[u], portalsUsed[u]);
            freeMinHeap(minHeap);
            return;
        }

        if (visited[u]) continue;
        visited[u] = true;

        // Verifica todos os vizinhos
        for (int v = 0; v < V; v++) {
            if (graph->adjMatrix[u][v] < INF) { // Se há uma aresta
                double weight = graph->adjMatrix[u][v];
                double newDist = dist[u] + weight;
                int newPortalsUsed = portalsUsed[u] + (weight == 0 ? 1 : 0);

                if (newDist <= s && newPortalsUsed <= k && !visited[v] && newDist < dist[v]) {
                    dist[v] = newDist;
                    portalsUsed[v] = newPortalsUsed;
                    decreaseKey(minHeap, v, newDist, newPortalsUsed);
                }
            }
        }
    }
    
    if (dist[dest] == INF) {
        printf("No path found from %d to %d within %d portals.\n", src, dest, k);
    } else {
        printf("Shortest path from %d to %d is %.2f with %d portals used.\n", src, dest, dist[dest], portalsUsed[dest]);
    }
    freeMinHeap(minHeap);
}



void aStar(Graph* graph, int src, int dest, double s, int k) {
    int V = graph->V;
    double dist[V];
    int portalsUsed[V];
    double heuristic[V];
    double h = 0;
    bool visited[V];
    MinHeap* minHeap = createMinHeap(V);

    if (!minHeap) {
        fprintf(stderr, "Failed to create MinHeap\n");
        return;
    }

    // Inicialização
    for (int i = 0; i < V; ++i) {
        dist[i] = INF;
        portalsUsed[i] = 0;
        heuristic[i] = INF;
        visited[i] = false;
        minHeap->array[i] = newMinHeapNode(i, dist[i], 0);
        minHeap->pos[i] = i;
    }

    minHeap->array[src] = newMinHeapNode(src, 0, 0);
    minHeap->pos[src] = src;
    dist[src] = 0;
    heuristic[src] = euclideanDistance(graph, src, dest);
    decreaseKey(minHeap, src, dist[src] + heuristic[src], 0);
    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        if (!minHeapNode) {
            fprintf(stderr, "Failed to extract min node. Heap might be empty.\n");
            break;
        }
        int u = minHeapNode->v;
        free(minHeapNode);

        if (visited[u]) continue;
        visited[u] = true;

        if (u == dest) {
            printf("Found path with distance %f and %d portals used\n", dist[u], portalsUsed[u]);
            freeMinHeap(minHeap);
            return;
        }

        // Verifica todos os vizinhos
        for (int v = 0; v < V; v++) {
            if (graph->adjMatrix[u][v] < INF) { // Se há uma aresta
                double weight = graph->adjMatrix[u][v];
                double newDist = dist[u] + weight;
                int newPortalsUsed = portalsUsed[u] + (weight == 0 ? 1 : 0);
                double f = newDist + h;
                if (u == dest) {
                    h = euclideanDistance(graph, v, dest);
                    printf("Found path with distance %f and %d portals used\n", dist[u], portalsUsed[u]);
                    freeMinHeap(minHeap);
                }
                if (newDist <= s && newPortalsUsed <= k && !visited[v] && newDist < dist[v]) {
                    dist[v] = newDist;
                    portalsUsed[v] = newPortalsUsed;
                    decreaseKey(minHeap, v, f, newPortalsUsed);
                }
            }
        }
    }

    printf("No path found\n");
    freeMinHeap(minHeap);
}


