#ifndef HEAPH_H
#define HEAPH_H

typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
} AdjList;

typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

AdjListNode* newAdjListNode(int dest, int weight);
Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest, int weight);
void addPortal(Graph* graph, int src, int dest);
void dijkstra(Graph* graph, int src, int dest, int s, int k);
double euclideanDistance(int x1, int y1, int x2, int y2);
void aStar(Graph* graph, int src, int dest, int s, int k, int* xCoords, int* yCoords);

#endif