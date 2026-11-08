#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t head;
    size_t count;
};

Queue* queue_create()
{
    Queue* queue = new Queue;

    queue->vector = vector_create();
    vector_resize(queue->vector, 4);

    queue->head = 0;
    queue->count = 0;

    return queue;
}

void queue_delete(Queue* queue)
{
    if (queue == nullptr)
        return;

    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue == nullptr)
        return;

    size_t capacity = vector_size(queue->vector);

    if (queue->count == capacity)
    {
        size_t newCapacity = capacity * 2;

        Vector* newVector = vector_create();
        vector_resize(newVector, newCapacity);

        for (size_t i = 0; i < queue->count; ++i)
        {
            size_t oldIndex = (queue->head + i) % capacity;
            Data value = vector_get(queue->vector, oldIndex);

            vector_set(newVector, i, value);
        }

        vector_delete(queue->vector);

        queue->vector = newVector;
        queue->head = 0;
    }

    capacity = vector_size(queue->vector);

    size_t tail = (queue->head + queue->count) % capacity;

    vector_set(queue->vector, tail, data);

    ++queue->count;
}

Data queue_get(const Queue* queue)
{
    if (queue == nullptr || queue->count == 0)
        return Data{};

    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue* queue)
{
    if (queue == nullptr || queue->count == 0)
        return;

    size_t capacity = vector_size(queue->vector);

    queue->head = (queue->head + 1) % capacity;

    --queue->count;
}

bool queue_empty(const Queue* queue)
{
    return queue == nullptr || queue->count == 0;
}
