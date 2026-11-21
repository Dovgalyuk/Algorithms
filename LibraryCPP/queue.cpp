#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* items;
    size_t head;
    size_t count;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->items = vector_create();
    queue->head = 0;
    queue->count = 0;

    vector_resize(queue->items, 8);
    return queue;
}

void queue_delete(Queue* queue)
{
    if (queue == nullptr)
        return;

    vector_delete(queue->items);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue == nullptr)
        return;

    if (queue->count == vector_size(queue->items))
    {
        size_t new_capacity = vector_size(queue->items) * 2;
        Vector* new_items = vector_create();
        vector_resize(new_items, new_capacity);

        for (size_t i = 0; i < queue->count; ++i)
        {
            size_t old_index = (queue->head + i) % vector_size(queue->items);
            vector_set(new_items, i, vector_get(queue->items, old_index));
        }

        vector_delete(queue->items);
        queue->items = new_items;
        queue->head = 0;
    }

    size_t tail = (queue->head + queue->count) % vector_size(queue->items);
    vector_set(queue->items, tail, data);
    ++queue->count;
}

Data queue_get(const Queue* queue)
{
    if (queue == nullptr || queue->count == 0)
        return Data{};

    return vector_get(queue->items, queue->head);
}

void queue_remove(Queue* queue)
{
    if (queue == nullptr || queue->count == 0)
        return;

    queue->head = (queue->head + 1) % vector_size(queue->items);
    --queue->count;

    if (queue->count == 0)
        queue->head = 0;
}

bool queue_empty(const Queue* queue)
{
    return queue == nullptr || queue->count == 0;
}
