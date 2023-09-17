#include <stdlib.h>
#include "queue.h"

typedef struct Queue
{
} Queue;

Queue *queue_create(FFree f)
{
    return malloc(sizeof(Queue));
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    free(queue);
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
