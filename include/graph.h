#ifndef GRAPH_H
#define GRAPH_H

typedef struct AdjListNode {
    int dest;
    double weight;
    int val;
    int x, y;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    struct AdjListNode *head;
} AdjList;

typedef struct Graph {
    int V;
    struct AdjList* array;
} Graph;

AdjListNode* newAdjListNode(int dest, int x, int y, double weight);
Graph* createGraph(int V);
void freeGraph(Graph* graph);
void getVertexPosition(Graph* graph, int vertex, int* x, int* y);
void addPosition(Graph* graph, int x, int y, int val);
void addEdge(Graph* graph, int src, int dest);
void addPortal(Graph* graph, int src, int dest);
void dijkstra(Graph* graph, int src, int dest, int s, int k);
void aStar(Graph* graph, int src, int dest, int s, int k, int* xCoords, int* yCoords);

#endif // GRAPH_H
