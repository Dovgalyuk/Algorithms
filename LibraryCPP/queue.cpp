#include "queue.h"

struct Queue
{
    size_t head;
    size_t tail;
    Vector* Q;
    Queue()
    {
        head = 0;
        tail = 0;
        Q = vector_create();
    }
    ~Queue()
    {
        vector_delete(Q);
    }
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (vector_size(queue->Q) == 0) vector_resize(queue->Q, 5);
    if (queue->tail + 1 == queue->head)
    {
        vector_set(queue->Q, queue->tail, data);
        queue->tail++;
        Vector* Q = vector_create();
        vector_resize(Q, vector_size(queue->Q) + 3);
        int j = 0;
        for (int i = queue->head; i < vector_size(queue->Q); i++, j++)
        {
            vector_set(Q, j, vector_get(queue->Q, i));
        }
        for (int i = 0; i < queue->tail; i++, j++)
        {
            vector_set(Q, j, vector_get(queue->Q, i));
        }
        vector_delete(queue->Q);
        queue->Q = Q;
        queue->head = 0;
        queue->tail = vector_size(queue->Q) - 3;
    }
    else
    {
        if (queue->tail != vector_size(queue->Q) - 1)
        {
            vector_set(queue->Q, queue->tail, data);
            queue->tail++;
        }
        else if (queue->head != 0)
        {
            vector_set(queue->Q, queue->tail, data);
            queue->tail = 0;
        }
        else
        {
            vector_set(queue->Q, queue->tail, data);
            queue->tail++;
            vector_resize(queue->Q, vector_size(queue->Q) + 3);
        }
    }
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->Q, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue->head < vector_size(queue->Q) - 1)
        queue->head++;
    else if (queue->head != queue->tail)
        queue->head = 0;
}

bool queue_empty(const Queue *queue)
{
    return queue->head == queue->tail;
}
