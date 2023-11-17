#include "priorityQueue.h"

struct PriorityQueue
{
   BinaryHeap* heap;
};

PriorityQueue* priorityQueue_create(const size_t size)
{
   PriorityQueue* queue = new PriorityQueue;
   queue->heap = binaryHeap_create(size);
   return queue;
}

void priorityQueue_delete(PriorityQueue* queue)
{
   binaryHeap_delete(queue->heap);
   delete queue;
}

void priorityQueue_insert(PriorityQueue* queue, HuffmanNode* node)
{
   binaryHeap_insert(queue->heap, node);
}

HuffmanNode* priorityQueue_getNode(PriorityQueue* queue)
{
   return BinaryHeap_getNode(queue->heap);
}

unsigned long long int priorityQueue_getNodeWeight(PriorityQueue* queue)
{
   return binaryHeap_getNodeWeight(queue->heap);
}

unsigned char priorityQueue_getNodeSymbol(PriorityQueue* queue)
{
   return binaryHeap_getNodeSymbol(queue->heap);
}

size_t priorityQueue_getSize(PriorityQueue* queue)
{
   return binaryHeap_getSize(queue->heap);
}

bool priorityQueue_nodeIsLeaf(PriorityQueue* queue)
{
   return binaryHeap_nodeIsLeaf(queue->heap);
}

void priorityQueue_remove(PriorityQueue* queue)
{
   binaryHeap_extractMin(queue->heap);
}

bool priorityQueue_empty(PriorityQueue* queue)
{
   return binaryHeap_getSize(queue->heap) == 0;
}
