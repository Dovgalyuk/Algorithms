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
        vector_resize(queueVector, 4);
        first = 0;
        last = 0;
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
    Vector* qVector = queue->queueVector;
    if (queue->last >= vector_size(queue->queueVector) - 1 && queue->first==0)
    {
        vector_resize(queue->queueVector, vector_size(queue->queueVector) + 1);
    }
    else if (queue->last + 1 == queue->first)
    {
        Vector* tmpV = vector_create();
        vector_resize(tmpV, vector_size(queue->queueVector) + 1);
        size_t s = 0;

        for (int i = queue->first; i < vector_size(queue->queueVector); i++)
        {
            vector_set(tmpV, s, vector_get(queue->queueVector, i));
            s++;
        }
        for (int i = 0; i <= queue->last; i++)
        {
            vector_set(tmpV, s, vector_get(queue->queueVector, i));
            s++;
        }
        queue->queueVector = tmpV;
        vector_delete(qVector);
        queue->first = 0;
        queue->last = s + 1;
    }
    vector_set(queue->queueVector, queue->last, data);
    if (queue->last == vector_size(queue->queueVector) - 1)
    {
        queue->last = 0;
    }
    else
    {
        queue->last++;
    }
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->queueVector, queue->first);
}

void queue_remove(Queue *queue)
{
    if (!queue_empty(queue))
    {
        if (queue->first >= vector_size(queue->queueVector) - 1)
        {
            queue->first = 0;
        }
        else
        {
            queue->first++;
        }
    }
}

bool queue_empty(const Queue *queue)
{
    if (queue->last == queue->first)
    {
        return true;
    }
    else
    {
        return false;
    }
}
