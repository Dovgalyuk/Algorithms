#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *data;

    Queue()
    {
        data = vector_create();
    }
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->data);

    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    vector_resize(queue->data, vector_size(queue->data) + 1);
    
    vector_set(queue->data, vector_size(queue->data) - 1, data);
}

Data queue_get(const Queue *queue)
{
    if (vector_size(queue->data) != 0)
        return vector_get(queue->data, 0);
    else
        return (Data)0;
}

void queue_remove(Queue *queue)
{
    if (!queue_empty(queue))
    {
        for (size_t i = 0; i < vector_size(queue->data) - 1; ++i)
            vector_set(queue->data, i, vector_get(queue->data, i + 1));

        vector_resize(queue->data, vector_size(queue->data) - 1);
    }
}

bool queue_empty(const Queue *queue)
{
    if (vector_size(queue->data) == 0)
        return true;
    else
        return false;
}
