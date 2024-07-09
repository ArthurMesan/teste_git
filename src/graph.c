#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include "graph.h"
#include "heap.h"

#define INF INT_MAX


AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void addPortal(Graph* graph, int src, int dest) {
    addEdge(graph, src, dest, 0);
}

void dijkstra(Graph* graph, int src, int dest, int s, int k) {
    int V = graph->V;
    int dist[V];
    int portalsUsed[V];
    for (int i = 0; i < V; ++i) {
        dist[i] = INF;
        portalsUsed[i] = 0;
    }

    MinHeap* minHeap = createMinHeap(V);

    minHeap->array[0] = newMinHeapNode(src, 0, 0);
    minHeap->pos[src] = 0;
    dist[src] = 0;
    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        if (u == dest) {
            printf("Found path with distance %d and %d portals used\n", dist[u], portalsUsed[u]);
            return;
        }

        AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            int weight = pCrawl->weight;
            int newDist = dist[u] + weight;
            int newPortalsUsed = portalsUsed[u] + (weight == 0 ? 1 : 0);

            if (newDist <= s && newPortalsUsed <= k && newDist < dist[v]) {
                dist[v] = newDist;
                portalsUsed[v] = newPortalsUsed;
                decreaseKey(minHeap, v, newDist, newPortalsUsed);
            }
            pCrawl = pCrawl->next;
        }
    }

    printf("No path found\n");
}

double euclideanDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void aStar(Graph* graph, int src, int dest, int s, int k, int* xCoords, int* yCoords) {
    int V = graph->V;
    int dist[V];
    int portalsUsed[V];
    for (int i = 0; i < V; ++i) {
    dist[i] = INF;
    portalsUsed[i] = 0;
    }

    MinHeap* minHeap = createMinHeap(V);

    minHeap->array[0] = newMinHeapNode(src, 0, 0);
    minHeap->pos[src] = 0;
    dist[src] = 0;
    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        if (u == dest) {
            printf("Found path with distance %d and %d portals used\n", dist[u], portalsUsed[u]);
            return;
        }

        AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            int weight = pCrawl->weight;
            int newDist = dist[u] + weight;
            int newPortalsUsed = portalsUsed[u] + (weight == 0 ? 1 : 0);

            double heuristic = euclideanDistance(xCoords[v], yCoords[v], xCoords[dest], yCoords[dest]);
            int fScore = newDist + heuristic;

            if (newDist <= s && newPortalsUsed <= k && fScore < dist[v]) {
                dist[v] = fScore;
                portalsUsed[v] = newPortalsUsed;
                    decreaseKey(minHeap, v, fScore, newPortalsUsed);
            }
            pCrawl = pCrawl->next;
        }
    }
    printf("No path found\n");
}

