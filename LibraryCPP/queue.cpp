#include "queue.h"
#include "vector.h"

struct Queue
{
    size_t head;
    size_t tail;
    size_t end;
    Vector* Q;
    Queue()
    {
        head = 0;
        tail = 0;
        end = 5;
        Q = vector_create();
    }
    ~Queue()
    {
        vector_delete(Q);
    }
};

Queue* queue_create()
{
    return new Queue;
}

void queue_delete(Queue* queue)
{
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (vector_size(queue->Q) == 0) vector_resize(queue->Q, queue->end);
    if (queue->tail + 1 == queue->head)
    {
        vector_set(queue->Q, queue->tail, data);
        queue->tail++;
        queue->end += 3;
        Vector* Q = vector_create();
        vector_resize(Q, queue->end);
        int j = 0;
        for (int i = queue->head; i < queue->end-3; i++, j++)
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
        queue->tail = queue->end - 3;
    }
    else
    {
        if (queue->tail != queue->end - 1)
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
            queue->end += 3;
            vector_resize(queue->Q, queue->end);
        }
    }
}

Data queue_get(const Queue* queue)
{
    return vector_get(queue->Q, queue->head);
}

void queue_remove(Queue* queue)
{
    if (queue->head < queue->end-1)
        queue->head++;
    else if (queue->head != queue->tail)
        queue->head = 0;
}

bool queue_empty(const Queue* queue)
{
    return queue->head == queue->tail;
}
