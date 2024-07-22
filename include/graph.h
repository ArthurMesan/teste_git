#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

// Estrutura para armazenar as coordenadas dos vértices
typedef struct Vertex {
    double x, y;  // Coordenadas dos vértices
} Vertex;

// Estrutura para armazenar um nó da lista de adjacência
typedef struct AdjListNode {
    int dest;          // Vértice de destino
    double weight;     // Peso da aresta
    struct AdjListNode* next; // Próximo nó na lista de adjacência
} AdjListNode;

// Estrutura para uma lista de adjacência
typedef struct AdjList {
    AdjListNode* head; // Cabeça da lista
} AdjList;

// Estrutura para o grafo
typedef struct Graph {
    int V;             // Número de vértices
    double** adjMatrix; // Matriz de adjacência
    Vertex* vertices;  // Array de coordenadas dos vértices
} Graph;

// Função para criar um novo nó da lista de adjacência
//AdjListNode* newAdjListNode(int dest, double weight);

// Funções para gerenciar o grafo
Graph* createGraph(int V);
//void freeAdjListNode(AdjListNode* node);
void freeGraph(Graph* graph);
void addPortal(Graph* graph, int src, int dest);
void addEdge(Graph* graph, int src, int dest, double weight);
void addEdgeWithDistance(Graph* graph, int src, int dest);
void addVertexPosition(Graph* graph, int vertex, double x, double y);
void getVertexPosition(Graph* graph, int vertex, double* x, double* y);
double euclideanDistance(Graph* graph, int u, int v);
void printPath(int predecessors[], int current);
void dijkstra(Graph* graph, int src, int dest, double s, int k);
void aStar(Graph* graph, int src, int dest, double s, int k);

#endif // GRAPH_H

