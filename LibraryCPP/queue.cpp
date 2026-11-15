#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    size_t head;
    size_t count;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->vector = vector_create();
    vector_resize(queue->vector, 4);
    queue->head = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t size = vector_size(queue->vector);
    
    if (queue->count == size)
    {
        vector_resize(queue->vector, size * 2);
        for (size_t i = 0; i < queue->head; ++i)
        {
            vector_set(queue->vector, size + i, vector_get(queue->vector, i));
        }
    }

    size_t tail = (queue->head + queue->count) % vector_size(queue->vector);
    vector_set(queue->vector, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue->count == 0)
    {
        return;
    }

    queue->head++;
    
    if (queue->head == vector_size(queue->vector))
    {
        queue->head = 0;
    }

    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
