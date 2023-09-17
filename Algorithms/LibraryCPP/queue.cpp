#include "queue.h"

struct Queue
{
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
}

Data queue_get(const Queue *queue)
{
    return (Data)0;
}

void queue_remove(Queue *queue)
{
}

bool queue_empty(const Queue *queue)
{
    return true;
}
