#include <stdlib.h>
#include "vector.h"
#include "queue.h"

struct Queue
{
    Vector* vector;
    size_t size;
};

Queue *queue_create()
{
    Queue* new_queue = new Queue;
    new_queue->vector = vector_create();
    new_queue->size = 0;
    return new_queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    vector_set(queue->vector, queue->size, data);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if (queue->size != 0)
        return queue->vector->point[0];
    return (Data)0;
}

void queue_remove(Queue *queue)
{
    if (queue->size != 0)
    {
        queue->size--;
        for (size_t i = 0; i < queue->size; i++)
            queue->vector->point[i] = queue->vector->point[i + 1];
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
