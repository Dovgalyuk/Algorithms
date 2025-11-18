#include <stdlib.h>
#include "queue.h"

typedef struct Queue {
    Data d; 
} Queue;

Queue* queue_create(FFree f)
{
    (void)f;
    return malloc(sizeof(Queue));
}

void queue_delete(Queue* queue)
{
    (void)queue;
    free(queue);
}

void queue_insert(Queue* queue, Data data)
{
    (void)queue;
    (void)data;
}

Data queue_get(const Queue* queue)
{
    (void)queue;
    return 0;
}

void queue_remove(Queue* queue)
{
    (void)queue;
}

bool queue_empty(const Queue* queue)
{
    (void)queue;
    return true;
}
