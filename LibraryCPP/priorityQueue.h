#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "binaryHeap.h"

struct PriorityQueue;

PriorityQueue* priorityQueue_create(const size_t size);

void priorityQueue_delete(PriorityQueue* queue);

void priorityQueue_insert(PriorityQueue* queue, HuffmanNode* node);

HuffmanNode* priorityQueue_getNode(PriorityQueue* queue);

unsigned long long int priorityQueue_getNodeWeight(PriorityQueue* queue);

unsigned char priorityQueue_getNodeSymbol(PriorityQueue* queue);

size_t priorityQueue_getSize(PriorityQueue* queue);

bool priorityQueue_nodeIsLeaf(PriorityQueue* queue);

void priorityQueue_remove(PriorityQueue* queue);

bool priorityQueue_empty(PriorityQueue* queue);

#endif
