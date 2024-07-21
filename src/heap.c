#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

MinHeapNode* newMinHeapNode(int v, double dist, int portalsUsed) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    if (!minHeapNode) {
        perror("Failed to allocate memory for MinHeapNode");
        exit(EXIT_FAILURE);
    }
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    minHeapNode->portalsUsed = portalsUsed;
    return minHeapNode;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    
    if (!minHeap) {
        perror("Failed to allocate memory for MinHeap");
        exit(EXIT_FAILURE);
    }

    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    
    for (int i = 0; i < capacity; i++)
    {
        minHeap->pos[i] = -1;
    }
    
    if (!minHeap->pos) {
        perror("Failed to allocate memory for MinHeap position array");
        exit(EXIT_FAILURE);
    }

    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    
    if (!minHeap->array) {
        perror("Failed to allocate memory for MinHeap array");
        exit(EXIT_FAILURE);
    }

    minHeap->size = 0;
    minHeap->capacity = capacity;

    return minHeap;
}

void freeMinHeapNode(MinHeapNode* node) {
    free(node);
}


void freeMinHeap(MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; ++i) {
        freeMinHeapNode(minHeap->array[i]);
    }
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return NULL;
    }

    MinHeapNode* root = minHeap->array[0];
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}


void decreaseKey(MinHeap* minHeap, int v, double dist, int portalsUsed) {
    int i = minHeap->pos[v];

    minHeap->array[i]->dist = dist;
    minHeap->array[i]->portalsUsed = portalsUsed;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool isInMinHeap(MinHeap* minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}
