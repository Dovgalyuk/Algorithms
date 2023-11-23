#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <stdlib.h>

typedef int (*Comparator)(const void*, const void*);
typedef void (*Destructor)(void*);

struct BinaryHeap;

BinaryHeap* binaryHeap_create(const size_t size, Comparator comp, Destructor dest);

void binaryHeap_swapData(BinaryHeap* heap, const size_t firstIndex, const size_t secondIndex);

void binaryHeap_heapify(BinaryHeap* heap, int i);

void binaryHeap_insert(BinaryHeap* heap, void* node);

void* binaryHeap_extractMin(BinaryHeap* heap);

void* binaryHeap_getMin(BinaryHeap* heap);

size_t binaryHeap_getSize(BinaryHeap* heap);

void binaryHeap_delete(BinaryHeap* heap);

#endif