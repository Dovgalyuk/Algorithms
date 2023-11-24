#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "binaryHeap.h"

struct PriorityQueue;

PriorityQueue* priorityQueue_create(const size_t size, Comparator comp, Destructor dest);

void priorityQueue_delete(PriorityQueue* queue);

void priorityQueue_insert(PriorityQueue* queue, void* data);

void* priorityQueue_getMin(PriorityQueue* queue);

void* priorityQueue_extractMin(PriorityQueue* queue);

size_t priorityQueue_getSize(PriorityQueue* queue);

bool priorityQueue_empty(PriorityQueue* queue);

#endif