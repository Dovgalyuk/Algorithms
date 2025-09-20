/*#include "queue.h"

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
*/


#include "queue.h"

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

struct Queue
{
};

Queue* queue_create()
{
    return new Queue;
}

void queue_delete(Queue* queue)
{
    // TODO: free queue items
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    UNUSED(queue);
    UNUSED(data);
}

Data queue_get(const Queue* queue)
{
    UNUSED(queue);
    return (Data)0;
}

void queue_remove(Queue* queue)
{
    UNUSED(queue);
}

bool queue_empty(const Queue* queue)
{
    UNUSED(queue);
    return true;
}