#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

typedef struct MinHeapNode {
    int v;
    int dist;
    int portalsUsed;
} MinHeapNode;

typedef struct MinHeap {
    int size;
    int capacity;
    int *pos;
    MinHeapNode **array;
} MinHeap;

MinHeapNode* newMinHeapNode(int v, int dist, int portalsUsed);
MinHeap* createMinHeap(int capacity);
void freeMinHeap(MinHeap* minHeap);
void freeMinHeapNode(MinHeapNode* node);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
int isEmpty(MinHeap* minHeap);
MinHeapNode* extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int v, int dist, int portalsUsed);
bool isInMinHeap(MinHeap* minHeap, int v);

#endif // HEAP_H
