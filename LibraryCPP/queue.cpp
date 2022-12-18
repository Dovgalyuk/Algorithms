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

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->queueVector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->last == vector_size(queue->queueVector) - 1)
    {
        vector_resize(queue->queueVector, vector_size(queue->queueVector) + 1);
    }
    if (queue->first == -1)
    {
        queue->first = 0;
    }
    queue->last++;
    vector_set(queue->queueVector, queue->last, data);
    /*if (queue_empty(queue))
    {
        queue->first = 0;
        queue->last = 0;
    }
    else
    {
        queue->last++;
        if (queue->last == vector_size(queue->queueVector) - 1)
        {
            vector_resize(queue->queueVector, vector_size(queue->queueVector) + 1);
        }
    }
    vector_set(queue->queueVector, queue->last, data);*/
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->queueVector, queue->first);
}

void queue_remove(Queue *queue)
{
    if (!queue_empty(queue))
    {
        if (queue->first >= queue->last)
        {
            queue->first = -1;
            queue->last = -1;
        }
        else
        {
            queue->first++;
        }
    }
}

bool queue_empty(const Queue *queue)
{
    if (queue->last == -1 && queue->first == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
