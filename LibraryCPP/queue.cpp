#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* buf;
    size_t head;
    size_t count;
};

Queue* queue_create()
{
    Queue* q = new Queue;
    q->buf = vector_create();

    vector_resize(q->buf, 4);

    q->head = 0;
    q->count = 0;
    return q;
}

void queue_delete(Queue* queue)
{
    if (!queue)
        return;

    vector_delete(queue->buf);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    size_t capacity = vector_size(queue->buf);

    if (queue->count == capacity)
    {
        size_t old_capacity = capacity;

        Vector* new_buf = vector_create();
        vector_resize(new_buf, old_capacity * 2);

        for (size_t i = 0; i < queue->count; i++)
        {
            size_t idx = (queue->head + i) % old_capacity;
            vector_set(new_buf, i, vector_get(queue->buf, idx));
        }

        vector_delete(queue->buf);
        queue->buf = new_buf;
        queue->head = 0;
        capacity = vector_size(queue->buf);
    }

    size_t tail = (queue->head + queue->count) % capacity;
    vector_set(queue->buf, tail, data);
    ++queue->count;
}

Data queue_get(const Queue* queue)
{
    return vector_get(queue->buf, queue->head);
}

void queue_remove(Queue* queue)
{
    if (queue->count == 0)
        return;

    queue->head = (queue->head + 1) % vector_size(queue->buf);
    --queue->count;
}

bool queue_empty(const Queue* queue)
{
    return queue->count == 0;
}