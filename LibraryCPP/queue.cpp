#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    size_t first;
    size_t size;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->first = 0;
    queue->size = 0;
    queue->vector = vector_create();

    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    vector_resize(queue->vector, vector_size(queue->vector) + 1);
    vector_set(queue->vector,vector_size(queue->vector) - 1, data);
    queue->size += 1;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->first);
}

void queue_remove(Queue *queue)
{
    queue->first += 1;
    queue->size -= 1;

    if(queue->size <= 0)
    {
        queue->first = 0;
        queue->size = 0;
        vector_resize(queue->vector, 0);
    }
}

bool queue_empty(const Queue *queue)
{
    if(queue->size <= 0)
        return true;
        
    return false;
}
