#include "queue.h"

struct Queue
{
    Vector *buf;
    size_t head;
    size_t count;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->buf = vector_create();
    queue->head = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->buf);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t cap = vector_size(queue->buf);
    if (queue->count == cap)
    {
        size_t newCap = (cap == 0) ? 1 : cap * 2;
        if (queue->head != 0 && cap != 0)
        {
            for (size_t i = 0; i < queue->count; ++i)
            {
                size_t idx = (queue->head + i) % cap;
                Data v = vector_get(queue->buf, idx);
                vector_set(queue->buf, i, v);
            }
            queue->head = 0;
        }

        vector_resize(queue->buf, newCap);
    }

    cap = vector_size(queue->buf);
    size_t tail = (queue->head + queue->count) % cap;
    vector_set(queue->buf, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->buf, queue->head);
}

void queue_remove(Queue *queue)
{
    size_t cap = vector_size(queue->buf);
    queue->head = (queue->head + 1) % cap;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
