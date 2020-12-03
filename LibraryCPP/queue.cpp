#include <stdlib.h>
#include "vector.h"
#include "queue.h"

struct Queue
{
    Vector* vector;
    size_t begin;
    size_t size;
};

Queue *queue_create()
{
    Queue* new_queue = new Queue;
    new_queue->vector = vector_create();
    new_queue->begin = 0;
    new_queue->size = 0;
    return new_queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (vector_size(queue->vector) != 0 )
    {
        if (vector_size(queue->vector) == queue->size)
        {
            Vector* new_vector = vector_create();
            vector_resize(new_vector, vector_size(queue->vector) * 2);
            for (size_t i = 0; i < queue->size; i++)
                vector_set(new_vector, i, vector_get(queue->vector, (queue->begin + i) % vector_size(queue->vector)));
            vector_delete(queue->vector);
            queue->vector = new_vector;
            queue->begin = 0;
        }
        vector_set(queue->vector, (queue->begin + queue->size) % vector_size(queue->vector), data);
    }
    vector_set(queue->vector, 0, data);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if (queue->size != 0)
        return vector_get(queue->vector, queue->begin);
    return (Data)0;
}

void queue_remove(Queue *queue)
{
    if (queue->size != 0)
    {
        queue->begin = (queue->begin + 1) % vector_size(queue->vector);
        queue->size--;
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
