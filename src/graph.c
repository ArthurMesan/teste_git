#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include "graph.h"
#include "heap.h"

#define INF DBL_MAX

AdjListNode* newAdjListNode(int dest, double x, double y, double weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!newNode) {
        perror("Failed to allocate memory for new adjacency list node");
        exit(EXIT_FAILURE);
    }
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        perror("Failed to allocate memory for graph");
        exit(EXIT_FAILURE);
    }

    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    if (!graph->array) {
        perror("Failed to allocate memory for adjacency list array");
        free(graph);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}


void freeAdjListNode(AdjListNode* node) {
    while (node) {
        AdjListNode* temp = node;
        node = node->next;
        free(temp);
    }
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; ++i) {
        freeAdjListNode(graph->array[i].head);
        graph->array[i].head = NULL;
    }
    free(graph->array);
    free(graph);
}

void getVertexPosition(Graph* graph, int vertex, double* x, double* y) {
    if (graph->array[vertex].head != NULL) {
        *x = graph->array[vertex].head->x;
        *y = graph->array[vertex].head->y;
    } else {
        fprintf(stderr, "Vertex position not initialized\n");
        *x = *y = 0;  // Valor padrão ou ajuste necessário
    }
}

double euclideanDistance(Graph* graph, int u, int v) {
    double x1, y1, x2, y2;
    getVertexPosition(graph, u, &x1, &y1);
    getVertexPosition(graph, v, &x2, &y2);

    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

void addPosition(Graph* graph, double x, double y, int val) {
    if (val >= graph->V || val < 0) {
        fprintf(stderr, "Invalid position\n");
        return;
    }

    // Verifica se a posição já está inicializada
    if (graph->array[val].head == NULL) {
        graph->array[val].head = (AdjListNode*)malloc(sizeof(AdjListNode));
        if (!graph->array[val].head) {
            perror("Failed to allocate memory for AdjListNode");
            exit(EXIT_FAILURE);
        }
        graph->array[val].head->next = NULL; // Inicializa o próximo nó como NULL
    }

    // Atualiza as coordenadas no nó de posição
    graph->array[val].head->x = x;
    graph->array[val].head->y = y;
}


void addEdge(Graph* graph, int src, int dest) {
    if (src >= graph->V || dest >= graph->V || src < 0 || dest < 0) {
        fprintf(stderr, "Invalid edge\n");
        return;
    }

    // Calcula o peso usando as coordenadas reais
    double weight = euclideanDistance(graph, src, dest);
    AdjListNode* newNode = newAdjListNode(dest, 0, 0, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void addPortal(Graph* graph, int src, int dest) {
    if (src >= graph->V || dest >= graph->V || src < 0 || dest < 0) {
        fprintf(stderr, "Invalid edge\n");
        return;
    }

    // Calcula o peso usando as coordenadas reais
    double weight = 0;
    AdjListNode* newNode = newAdjListNode(dest, 0, 0, weight);
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



//void aStar(Graph* graph, int src, int dest, int s, int k, int* xCoords, int* yCoords) {
    /*int V = graph->V;
    int dist[V];
    int portalsUsed[V];
    for (int i = 0; i < V; ++i) {
        dist[i] = INF;
        portalsUsed[i] = 0;
    }

    MinHeap* minHeap = createMinHeap(V);

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
    minHeap->pos[src] = 0;
    dist[src] = 0;
    minHeap->size = V;
    printf("existe algum problema aqui?\n");
    while (!isEmpty(minHeap)) {
        printf("Existe algum problema aqui?\n");

        MinHeapNode* minHeapNode = extractMin(minHeap);//teste para extrair a minheap aqui
        
        if (!minHeapNode) {
            fprintf(stderr, "Failed to extract min node. Heap might be empty.\n");
            break;
        }
        int u = minHeapNode->v;
        free(minHeapNode);

        if (u == dest) {
            printf("Found path with distance %d and %d portals used\n", dist[u], portalsUsed[u]);
            freeMinHeap(minHeap);
            return;
        }

        AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            int weight = pCrawl->weight;
            int newDist = dist[u] + weight;
            int newPortalsUsed = portalsUsed[u] + (weight == 0 ? 1 : 0);

            double heuristic = euclideanDistance(xCoords[v], yCoords[v], xCoords[dest], yCoords[dest]);
            int f = newDist + (int)heuristic;

            if (newDist <= s && newPortalsUsed <= k && f < dist[v]) {
                dist[v] = f;
                portalsUsed[v] = newPortalsUsed;
                decreaseKey(minHeap, v, f, newPortalsUsed);
            }
            pCrawl = pCrawl->next;
        }
    }

    printf("No path found\n");
    freeMinHeap(minHeap);*/
//}

