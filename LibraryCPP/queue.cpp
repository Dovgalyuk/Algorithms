#include "queue.h"
#include "vector.h"
#include <cstddef>

struct Queue
{
    Vector* data;
    size_t  head;
    size_t  count;
};

Queue* queue_create()
{
    Queue* q = new Queue;
    q->data  = vector_create();
    vector_resize(q->data, 1);
    q->head  = 0;
    q->count = 0;
    return q;
}

void queue_delete(Queue* queue)
{
    if (!queue)
        return;

    vector_delete(queue->data);
    delete queue;
}

bool queue_empty(const Queue* queue)
{
    return queue->count == 0;
}

Data queue_get(const Queue* queue)
{
    return vector_get(queue->data, queue->head);
}

void queue_insert(Queue* queue, Data value)
{
    size_t capacity = vector_size(queue->data);

    if (queue->count == capacity)
    {
        size_t newCapacity = (capacity == 0 ? 1 : capacity * 2);

        Data* tmp = new Data[queue->count];
        for (size_t i = 0; i < queue->count; i++)
        {
            size_t idx = (queue->head + i) % capacity;
            tmp[i] = vector_get(queue->data, idx);
        }

        vector_resize(queue->data, newCapacity);

        for (size_t i = 0; i < queue->count; i++)
            vector_set(queue->data, i, tmp[i]);

        delete[] tmp;

        queue->head = 0;
        capacity = newCapacity;
    }

    size_t tail = (queue->head + queue->count) % capacity;
    vector_set(queue->data, tail, value);
    ++queue->count;
}

void queue_remove(Queue* queue)
{
    if (queue->count == 0)
        return;

    size_t capacity = vector_size(queue->data);
    queue->head = (queue->head + 1) % capacity;
    --queue->count;
}

