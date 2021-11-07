#include "queue.h"
#include "vector.h"

struct Queue
{
    size_t begin;
    size_t end;
    Vector* Q;
    Queue()
    {
        begin = 0;
        end = 0;
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
    vector_resize(queue->Q, vector_size(queue->Q) + 1);
    queue->end++;
    vector_set(queue->Q, queue->end - 1, data);
}

Data queue_get(const Queue* queue)
{
    return vector_get(queue->Q, queue->begin);
}

void queue_remove(Queue* queue)
{
    if (queue->begin < queue->end)
        queue->begin++;
}

bool queue_empty(const Queue* queue)
{
    return vector_get(queue->Q, queue->begin) == vector_get(queue->Q, queue->end);
}
