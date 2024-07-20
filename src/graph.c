#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "graph.h"
#include "heap.h"

#define INF INT_MAX

AdjListNode* newAdjListNode(int dest, int x, int y, double weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!newNode) {
        perror("Failed to allocate memory for AdjListNode");
        exit(EXIT_FAILURE);
    }
    newNode->dest = dest;
    newNode->x = x;
    newNode->y = y;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        perror("Failed to allocate memory for Graph");
        exit(EXIT_FAILURE);
    }
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    if (!graph->array) {
        perror("Failed to allocate memory for Graph array");
        free(graph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    for (size_t i = 0; i < V; i++)
        graph->array[i].head->val = i;
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

double euclideanDistance(Graph* graph, int u, int v) {
    int x1,y1,x2,y2;
    x1 = graph->array[u].head->x;
    y1 = graph->array[u].head->y;
    x2 = graph->array[v].head->x;
    y2 = graph->array[v].head->y;
    double valor = ((x1- x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    if (valor < 0){
        valor = valor*(-1);
    }
    return sqrt(valor);
}

void addPosition(Graph* graph, int x, int y, int val){
    graph->array[val].head->x = x;
    graph->array[val].head->y = y;
}

void addEdge(Graph* graph, int src, int dest) {
    double weight = euclideanDistance(graph, src, dest);
    int x = graph->array[dest].head->x;
    int y = graph->array[dest].head->y;
    AdjListNode* newNode = newAdjListNode(dest, x, y, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void addPortal(Graph* graph, int src, int dest) {
    addEdge(graph, src, dest);
}

void dijkstra(Graph* graph, int src, int dest, int s, int k) {
    int V = graph->V;
    int dist[V];
    int portalsUsed[V];
    MinHeap* minHeap = createMinHeap(V);

    if (!minHeap) {
        fprintf(stderr, "Failed to create MinHeap\n");
        return;
    }

    for (int i = 0; i < V; ++i) {
        dist[i] = INF;
        minHeap->array[i] = newMinHeapNode(i, dist[i], 0);
        minHeap->pos[i] = i;
    }

    minHeap->array[src] = newMinHeapNode(src, 0, 0);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src], 1);
    minHeap->size = V;
    //minHeapify(minHeap, 0);
    while (!isEmpty(minHeap)) {


        MinHeapNode* minHeapNode = extractMin(minHeap);
        
        if (!minHeapNode) {
            fprintf(stderr, "Failed to extract min node. Heap might be empty.\n");
            break;
        }
        int u = minHeapNode->v;
    
        AdjListNode* pCrawl = graph->array[u].head;
        if (u == dest) {
            printf("Found path with distance %d and %d portals used\n", dist[u], portalsUsed[u]);
            freeMinHeap(minHeap);
            freeAdjListNode(pCrawl);
            freeMinHeapNode(minHeapNode);
            return;
        }
        free(minHeapNode);
        while (pCrawl) {
            int v = pCrawl->dest;
            int weight = pCrawl->weight;
            int newDist = dist[u] + weight;
            int newPortalsUsed = portalsUsed[u] + (weight == 0 ? 1 : 0);

            if (newDist <= s && newDist < dist[v]) {
                dist[v] = newDist;
                portalsUsed[v] = newPortalsUsed;
                decreaseKey(minHeap, v, newDist, newPortalsUsed);
            }
            pCrawl = pCrawl->next;
        }
    }
    printf("No path found\n");
}

void aStar(Graph* graph, int src, int dest, int s, int k, int* xCoords, int* yCoords) {
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
}

