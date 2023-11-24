#include "priorityQueue.h"

struct PriorityQueue
{
    BinaryHeap* heap;
};

PriorityQueue* priorityQueue_create(const size_t size, Comparator comp, Destructor dest)
{
    PriorityQueue* queue = new PriorityQueue;
    queue->heap = binaryHeap_create(size, comp, dest);
    return queue;
}

void priorityQueue_delete(PriorityQueue* queue)
{
    binaryHeap_delete(queue->heap);
    delete queue;
}

void priorityQueue_insert(PriorityQueue* queue, void* data)
{
    binaryHeap_insert(queue->heap, data);
}

void* priorityQueue_getMin(PriorityQueue* queue)
{
    return binaryHeap_getMin(queue->heap);
}

void* priorityQueue_extractMin(PriorityQueue* queue)
{
    return binaryHeap_extractMin(queue->heap);
}

size_t priorityQueue_getSize(PriorityQueue* queue)
{
    return binaryHeap_getSize(queue->heap);
}

bool priorityQueue_empty(PriorityQueue* queue)
{
    return binaryHeap_getSize(queue->heap) == 0;
}