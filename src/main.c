#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <limits.h>
#include "graph.h"
#include "heap.h"


#define INF INT_MAX

int main() {
    int V = 5;
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 20);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 2, 3, 10);
    addEdge(graph, 4, 3, 30);

    addPortal(graph, 0, 3);

    //int xCoords[] = {0, 1, 2, 3, 4}; // Coordenadas X das clareiras
    //int yCoords[] = {0, 1, 2, 3, 4}; // Coordenadas Y das clareiras

    int s = 40; // Energia disponível
    int k = 1;  // Máximo de portais

    printf("Dijkstra Modified:\n");
    dijkstra(graph, 0, 3, s, k);

    //printf("A* Modified:\n");
    //aStar(graph, 0, 3, s, k, xCoords, yCoords);


    freeGraph(graph);
    
    return 0;
}
/*int main() {
    int V = 5;  // Número de vértices
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 5);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 3, 4, 6);make

    printf("Graph created successfully!\n");

    // Teste dijkstra
    int src = 0, dest = 3;
    int s = 20, k = 2;
    printf("\nRunning Dijkstra's algorithm from vertex %d to vertex %d with s=%d and k=%d:\n", src, dest, s, k);
    dijkstra(graph, src, dest, s, k);

    // Teste aStar (supondo que tenhamos coordenadas x e y dos vértices)
    //int xCoords[] = {0, 2, 4, 7, 9};
    //int yCoords[] = {0, 1, 3, 5, 8};
    //printf("\nRunning A* algorithm from vertex %d to vertex %d with s=%d and k=%d:\n", src, dest, s, k);
    //aStar(graph, src, dest, s, k, xCoords, yCoords);
    return 0;
}*/
/*int main() {
    int V = 5;
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 20);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 3, 10);
    addEdge(graph, 3, 4, 5);
    addPortal(graph, 0, 3);

    MinHeap* heap = createMinHeap(V);
    for (int i = 0; i < V; i++) {
        MinHeapNode* node = newMinHeapNode(i, i * 10, 0);
        heap->array[i] = node;
        heap->pos[i] = i;
        heap->size++;
    }

    MinHeapNode* minNode = extractMin(heap);
    if (minNode != NULL) {
        printf("Extracted min node: v=%d, dist=%d, portalsUsed=%d\n", minNode->v, minNode->dist, minNode->portalsUsed);
        free(minNode);
    } else {
        printf("No node extracted, heap was empty\n");
    }

    freeMinHeap(heap);
    freeGraph(graph);

    return 0;
}*/


/*int main() {
    int V = 5;
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 20);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 3, 10);
    addEdge(graph, 3, 4, 5);
    addPortal(graph, 0, 3);

    MinHeap* heap = createMinHeap(V);
    for (int i = 0; i < V; i++) {
        MinHeapNode* node = newMinHeapNode(i, i * 10, 0);
        heap->array[i] = node;
        heap->pos[i] = i;
        heap->size++;
    }

    MinHeapNode* minNode = extractMin(heap);
    if (minNode != NULL) {
        printf("Extracted min node: v=%d, dist=%d, portalsUsed=%d\n", minNode->v, minNode->dist, minNode->portalsUsed);
        free(minNode);
    } else {
        printf("No node extracted, heap was empty\n");
    }

    freeMinHeap(heap);
    freeGraph(graph);

    return 0;
}*/
//validar minHeap

/*int main() {
    int V = 9;
    MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        minHeap->array[v] = newMinHeapNode(v, INT_MAX, 0);
        minHeap->pos[v] = v;
    }

    minHeap->array[0]->dist = 0;
    minHeap->size = V;

    MinHeapNode* minNode = extractMin(minHeap);
    printf("Vertex: %d, Distance: %d\n", minNode->v, minNode->dist);

    free(minNode);
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);

    return 0;
}*/

//validar grafos

/*int main() {
    int V = 5;  // Número de vértices
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 5);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 3, 4, 6);

    printf("Graph created successfully!\n");

    // Teste outras funções aqui, como dijkstra e aStar

    freeGraph(graph);
    return 0;
}*/

//validar arestas e portais


/*int main() {
    int V = 5;  // Número de vértices
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 5);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 3, 4, 6);
    addPortal(graph, 2, 4);

    printf("Graph created successfully!\n");

    // Verificar se as arestas foram adicionadas corretamente
    printf("Adjacency list representation of graph:\n");
    for (int i = 0; i < V; ++i) {
        AdjListNode* crawl = graph->array[i].head;
        printf("Vertex %d:", i);
        while (crawl) {
            printf(" -> %d(%d)", crawl->dest, crawl->weight);
            crawl = crawl->next;
        }
        printf("\n");
    }

    freeGraph(graph);
    return 0;
}*/

//teste dijkstra e a *



/*int main() {
    int V = 9;
    MinHeap* minHeap = createMinHeap(V);

    // Inicialização do heap mínimo com nós fictícios
    for (int v = 0; v < V; ++v) {
        minHeap->array[v] = newMinHeapNode(v, INT_MAX, 0); // Criando nós com distância infinita
        minHeap->pos[v] = v; // Definindo as posições no heap
    }

    // Definindo a distância do nó inicial como 0
    minHeap->array[0]->dist = 0;
    minHeap->size = V;

    printf("Extraindo nós mínimos do heap:\n");

    // Extrair nós mínimos até que o heap esteja vazio
    while (!isEmpty(minHeap)) {
        MinHeapNode* minNode = extractMin(minHeap);
        printf("Vertex: %d, Distance: %d\n", minNode->v, minNode->dist);
        free(minNode); // Liberando o nó extraído
    }

    // Liberando memória alocada para o heap mínimo
    //free(minHeap->array);
    //free(minHeap->pos);
    //free(minHeap);
    freeMinHeap(minHeap);
    return 0;
}*/
