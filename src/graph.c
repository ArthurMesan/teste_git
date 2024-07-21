#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include "graph.h"
#include "heap.h"

#define INF DBL_MAX

AdjListNode* newAdjListNode(int dest, double weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Função para criar um grafo com V vértices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    graph->vertices = (Vertex*)malloc(V * sizeof(Vertex));
    
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
        graph->vertices[i].x = 0.0;
        graph->vertices[i].y = 0.0;
    }

    return graph;
}


// Função para liberar a memória de um nó da lista de adjacência
void freeAdjListNode(AdjListNode* node) {
    free(node);
}

// Função para liberar a memória de um grafo
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        AdjListNode* node = graph->array[i].head;
        while (node) {
            AdjListNode* temp = node;
            node = node->next;
            freeAdjListNode(temp);
        }
    }
    free(graph->array);
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

/*double euclideanDistance(Graph* graph, int u, int v) {
    double x1, y1, x2, y2;
    getVertexPosition(graph, u, &x1, &y1);
    getVertexPosition(graph, v, &x2, &y2);

    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}*/

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
    // Adiciona dest à lista de adjacência de src
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Se o grafo é não direcionado, adicione src à lista de adjacência de dest
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Função para adicionar uma aresta com peso baseado na distância euclidiana
void addEdgeWithDistance(Graph* graph, int src, int dest) {
    double weight = euclideanDistance(graph, src, dest);
    addEdge(graph, src, dest, weight);
}

void addPortal(Graph* graph, int src, int dest) {
    if (src >= graph->V || dest >= graph->V || src < 0 || dest < 0) {
        fprintf(stderr, "Invalid edge\n");
        return;
    }

    // Calcula o peso usando as coordenadas reais
    double weight = 0;
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
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

        if (u == dest) {

            printf("Found path with distance %f and %d portals used\n", dist[u], portalsUsed[u]);
            free(minHeapNode);  // Liberar minHeapNode antes de retornar
            freeMinHeap(minHeap);
            return;
        }
        free(minHeapNode);  // Liberar minHeapNode após usá-lo

        if (visited[u]) continue;
        visited[u] = true;

        AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl) {
            int v = pCrawl->dest;
            double weight = pCrawl->weight;
            double newDist = dist[u] + weight;
            int newPortalsUsed = portalsUsed[u]+(weight == 0 ? 1 : 0);;  // Ajustar se os portais não estão sendo usados
            printf("Checking edge %d -> %d with weight %f, newDist %f, newPortalsUsed %d\n", u, v, weight, newDist, newPortalsUsed);
            if (newDist <= s && !visited[v] && newDist < dist[v]) {
                printf("Updating distance for node %d to %f and portals used to %d\n", v, newDist, newPortalsUsed);
                dist[v] = newDist;
                portalsUsed[v] = newPortalsUsed;
                decreaseKey(minHeap, v, newDist, newPortalsUsed);
            }
            printf("Processing node %d with distance %f and portals used %d\n", u, dist[u], portalsUsed[u]);
            pCrawl = pCrawl->next;
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
    double heuristic = 0;
    bool visited[V];
    MinHeap* minHeap = createMinHeap(V);
    for (int i = 0; i < V; ++i) {
        dist[i] = INF;
        portalsUsed[i] = 0;
        visited[i] = false;
        minHeap->array[i] = newMinHeapNode(i, dist[i], 0);
        minHeap->pos[i] = i;
    }

    if (!minHeap) {
        fprintf(stderr, "Failed to create MinHeap\n");
        return;
    }

    minHeap->array[0] = newMinHeapNode(src, 0, 0);
    if (!minHeap->array[0]) {
        freeMinHeap(minHeap);
        fprintf(stderr, "Failed to create MinHeapNode\n");
        return;
    }

    minHeap->array[src] = newMinHeapNode(src, 0, 0);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src], portalsUsed[src]);
    minHeap->size = V;

    while (!isEmpty(minHeap)) {

        MinHeapNode* minHeapNode = extractMin(minHeap);//teste para extrair a minheap aqui
        
        if (!minHeapNode) {
            fprintf(stderr, "Failed to extract min node. Heap might be empty.\n");
            break;
        }
        int u = minHeapNode->v;
        if (visited[u]) continue;
            visited[u] = true;
        free(minHeapNode);


        AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            double weight = pCrawl->weight;
            double newDist = dist[u] + weight;
            int newPortalsUsed = portalsUsed[u] + (weight == 0 ? 1 : 0);
            double f = newDist + heuristic;
            if (u == dest) {
            heuristic = euclideanDistance(graph, v, dest);
            printf("Found path with distance %f and %d portals used\n", dist[u], portalsUsed[u]);
            freeMinHeap(minHeap);
            return;
            }


            if (newDist <= s && !visited[v] && newDist < dist[v]) {
                dist[v] = f;
                portalsUsed[v] = newPortalsUsed;
                decreaseKey(minHeap, v, f, newPortalsUsed);
            }
            pCrawl = pCrawl->next;
        }
    }

    printf("No path found\n");
    freeMinHeap(minHeap);
}

