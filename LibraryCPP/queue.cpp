#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector = nullptr;
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;
};

Queue *queue_create()
{
    Queue *q = new Queue;
    q->vector = vector_create();
    vector_resize(q->vector, 4);
    return q;
}

void queue_delete(Queue *queue)
{
    if (!queue) return;
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t cap = vector_size(queue->vector);

    if (queue->count == cap)
    {
        size_t new_cap = cap * 2;
        Vector *nv = vector_create();
        vector_resize(nv, new_cap);

        for (size_t i = 0; i < queue->count; ++i)
        {
            size_t idx = (queue->head + i) % cap;
            vector_set(nv, i, vector_get(queue->vector, idx));
        }

        vector_delete(queue->vector);
        queue->vector = nv;
        queue->head = 0;
        queue->tail = queue->count;
        cap = new_cap;
    }

    vector_set(queue->vector, queue->tail, data);
    queue->tail = (queue->tail + 1) % cap;
    ++queue->count;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    size_t cap = vector_size(queue->vector);
    queue->head = (queue->head + 1) % cap;
    --queue->count;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}