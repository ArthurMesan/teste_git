#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct AdjListNode {
    int dest;
    double weight;
    double x, y;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
} AdjList;

typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

AdjListNode* newAdjListNode(int dest, double x, double y, double weight);
Graph* createGraph(int V);
void freeAdjListNode(AdjListNode* node);
void freeGraph(Graph* graph);
void addEdge(Graph* graph, int src, int dest);
void addPortal(Graph* graph, int src, int dest);
void addPosition(Graph* graph, double x, double y, int val);
void getVertexPosition(Graph* graph, int vertex, double* x, double* y);
double euclideanDistance(Graph* graph, int u, int v);
void dijkstra(Graph* graph, int src, int dest, double s, int k);

#endif // GRAPH_H
