#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "binaryHeap.h"
#include "huffmanTree.h"

struct PriorityQueue;

PriorityQueue* priorityQueue_create(const size_t size);

void priorityQueue_delete(PriorityQueue* queue);

void priorityQueue_insert(PriorityQueue* queue, HuffmanNode* node);

HuffmanNode* priorityQueue_getMin(PriorityQueue* queue);

HuffmanNode* priorityQueue_extractMin(PriorityQueue* queue);

size_t priorityQueue_getSize(PriorityQueue* queue);

bool priorityQueue_empty(PriorityQueue* queue);

#endif