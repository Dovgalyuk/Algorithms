#include "priorityQueue.h"

struct PriorityQueue
{
    BinaryHeap* heap;
};

PriorityQueue* priorityQueue_create(const size_t size)
{
    PriorityQueue* queue = new PriorityQueue;
    queue->heap = binaryHeap_create(size, huffmanNodeComparator, huffmanNodeDestructor);
    return queue;
}

void priorityQueue_delete(PriorityQueue* queue)
{
    binaryHeap_delete(queue->heap);
    delete queue;
}

void priorityQueue_insert(PriorityQueue* queue, HuffmanNode* node)
{
    binaryHeap_insert(queue->heap, (void*)node);
}

HuffmanNode* priorityQueue_getMin(PriorityQueue* queue)
{
    return (HuffmanNode*)binaryHeap_getMin(queue->heap);
}

HuffmanNode* priorityQueue_extractMin(PriorityQueue* queue)
{
    return (HuffmanNode*)binaryHeap_extractMin(queue->heap);
}

size_t priorityQueue_getSize(PriorityQueue* queue)
{
    return binaryHeap_getSize(queue->heap);
}

bool priorityQueue_empty(PriorityQueue* queue)
{
    return binaryHeap_getSize(queue->heap) == 0;
}