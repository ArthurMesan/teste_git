#ifndef GRAPH_H
#define GRAPH_H

typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    struct AdjListNode *head;
} AdjList;

typedef struct Graph {
    int V;
    struct AdjList* array;
} Graph;

AdjListNode* newAdjListNode(int dest, int weight);
Graph* createGraph(int V);
void freeGraph(Graph* graph);
void addEdge(Graph* graph, int src, int dest, int weight);
void addPortal(Graph* graph, int src, int dest);
void dijkstra(Graph* graph, int src, int dest, int s, int k);
void aStar(Graph* graph, int src, int dest, int s, int k, int* xCoords, int* yCoords);

#endif // GRAPH_H
