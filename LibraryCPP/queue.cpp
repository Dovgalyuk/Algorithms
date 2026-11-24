#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *buff;
    size_t head;
    size_t count;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->buff = vector_create();
    vector_resize(queue->buff, 4);
    queue->head = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    if (queue)
    {
        vector_delete(queue->buff);
        delete queue;
    }
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue)
    {
        return;
    }

    size_t cap = vector_size(queue->buff);
    if (queue->count == cap)
    {
        size_t new_cap = cap == 0 ? 4 : cap * 2;
        Vector *new_buff = vector_create();
        vector_resize(new_buff, new_cap);
        for (size_t i = 0; i < queue->count; ++i)
        {
            vector_set(new_buff, i, vector_get(queue->buff, (queue->head + i) % cap));
        }
        vector_delete(queue->buff);
        queue->buff = new_buff;
        queue->head = 0;
        cap = new_cap;
    }

    size_t tail = (queue->head + queue->count) % cap;
    vector_set(queue->buff, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (!queue || queue_empty(queue))
    {
        return (Data)0;
    }
    return vector_get(queue->buff, queue->head);
}

void queue_remove(Queue *queue)
{
    if (!queue || queue->count == 0)
    {
        return;
    }

    size_t cap = vector_size(queue->buff);
    queue->head = (queue->head + 1) % cap;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return !queue || queue->count == 0;
}
