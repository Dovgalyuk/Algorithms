#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    size_t first;
    size_t last;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->first = 0;
    queue->last = 0;
    queue->vector = vector_create();
    vector_resize(queue->vector, BUFFER_SIZE);

    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    vector_set(queue->vector,queue->last, data);
    queue->last = (queue->last + 1) % BUFFER_SIZE;
}

Data queue_get(const Queue *queue)
{
    if(queue->first != queue->last)
        return vector_get(queue->vector, queue->first);
    return (Data)0;
}

void queue_remove(Queue *queue)
{
    if(queue->first != queue->last)
        queue->first = (queue->first + 1) % BUFFER_SIZE;
}

bool queue_empty(const Queue *queue)
{
    if(queue->first == queue->last)
        return true;
        
    return false;
}
