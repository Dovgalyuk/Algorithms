#include <stdlib.h>
#include "vector.h"
#include "queue.h"

struct Queue
{
    Vector* vector;
    size_t begin;
    size_t queue_size;
    size_t vector_size;
};

Queue *queue_create()
{
    Queue* new_queue = new Queue;
    new_queue->vector = vector_create();
    new_queue->begin = 0;
    new_queue->queue_size = 0;
    new_queue->vector_size = 0;
    return new_queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->vector_size != 0 && queue->vector_size == queue->queue_size)
    {
        Vector* new_vector = vector_create();
        vector_resize(new_vector,queue->vector_size * 2);
        for (size_t i = 0; i < queue->queue_size; i++)
            vector_set(new_vector, i, vector_get(queue->vector, (queue->begin + i) % queue->vector_size));
        vector_delete(queue->vector);
        queue->vector = new_vector;
        queue->begin = 0;
        queue->vector_size *= 2;
    }
    vector_set(queue->vector, (queue->begin + queue->queue_size) % ( queue->vector_size ==0 ? ++queue->vector_size : queue->vector_size), data);
    queue->queue_size++;
}

Data queue_get(const Queue *queue)
{
    if (queue->queue_size != 0)
        return vector_get(queue->vector, queue->begin);
    return (Data)0;
}

void queue_remove(Queue *queue)
{
    if (queue->queue_size != 0)
    {
        queue->begin = (queue->begin + 1) % queue->vector_size;
        queue->queue_size--;
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->queue_size == 0;
}
