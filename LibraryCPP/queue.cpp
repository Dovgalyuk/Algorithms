#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* queueVector;
    int first;
    int last;
    Queue()
    {
        queueVector = vector_create();
        vector_resize(queueVector, 2);
        first = -1;
        last = -1;
    }
};

Queue* queue_create()
{
    return new Queue;
}

void queue_delete(Queue* queue)
{
    vector_delete(queue->queueVector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    size_t size = vector_size(queue->queueVector);
    if (queue_empty(queue))
    {
        queue->first = 0;
        queue->last = 0;
    }
    else if (queue->last % size == queue->first)
    {
        Vector* tmpV = vector_create();
        vector_resize(tmpV, size * 2);
        size_t s = 0;

        for (int i = queue->first; i < size; i++)
        {
            vector_set(tmpV, s, vector_get(queue->queueVector, i));
            s++;
        }
        for (int i = 0; i < queue->last; i++)
        {
            vector_set(tmpV, s, vector_get(queue->queueVector, i));
            s++;
        }
        vector_delete(queue->queueVector);
        queue->queueVector = tmpV;
        queue->first = 0;
        queue->last = size;
        size = vector_size(queue->queueVector);
    }
    int l = queue->last % size;
    vector_set(queue->queueVector, l, data);
    queue->last = l + 1;
}

Data queue_get(const Queue* queue)
{
    return vector_get(queue->queueVector, queue->first);
}

void queue_remove(Queue* queue)
{
    size_t size = vector_size(queue->queueVector);
    int f = queue->first;

    if (!queue_empty(queue))
    {
        f++;
        if (queue->last == f)
        {
            queue->first = -1;
            queue->last = -1;
        }
        else
        {
            queue->first = f % size;
        }
    }
}

bool queue_empty(const Queue* queue)
{
    return (queue->last == -1 && queue->first == -1);
}
