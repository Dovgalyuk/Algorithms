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
    if (!queue) return;
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue) return;
    size_t cap = vector_size(queue->vector);
    if (cap == 0)
    {
        vector_resize(queue->vector, 4);
        cap = 4;
    }
    else if (queue->count == cap)
    {
        size_t new_cap = cap * 2;
        Vector *new_vec = vector_create();
        vector_resize(new_vec, new_cap);
        for (size_t i = 0; i < queue->count; ++i)
        {
            vector_set(new_vec, i, vector_get(queue->vector, (queue->head + i) % cap));
        }
        vector_delete(queue->vector);
        queue->vector = new_vec;
        queue->head = 0;
        cap = new_cap;
    }

    size_t tail = (queue->head + queue->count) % cap;
    vector_set(queue->vector, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (!queue || queue->count == 0) return (Data)0;
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (!queue || queue->count == 0) return;
    size_t cap = vector_size(queue->vector);
    queue->head = (queue->head + 1) % cap;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return !queue || queue->count == 0;
}
