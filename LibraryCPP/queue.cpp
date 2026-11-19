#include "queue.h"
#include "vector.h"

#include <cassert>
#include <limits>
#include <stdexcept>

struct Queue
{
    Vector *buffer;
    size_t first;
    size_t count;
};

Queue *queue_create()
{
    return new Queue{vector_create(), 0, 0};
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->buffer);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t capacity = vector_size(queue->buffer);
    if (queue->count == capacity)
    {
        if (capacity > std::numeric_limits<size_t>::max() / 2)
            throw std::length_error("Queue очень большая");

        size_t old_capacity = capacity;
        capacity = old_capacity == 0 ? 1 : old_capacity * 2;
        vector_resize(queue->buffer, capacity);

        // Если очередь зашла за край, переносим её хвост за старый конец.
        for (size_t i = 0; i < queue->first; ++i)
            vector_set(queue->buffer, old_capacity + i, vector_get(queue->buffer, i));
    }

    size_t index = (queue->first + queue->count) % capacity;
    vector_set(queue->buffer, index, data);
    ++queue->count;
}

Data queue_get(const Queue *queue)
{
    assert(!queue_empty(queue));
    return vector_get(queue->buffer, queue->first);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue))
        return;

    queue->first = (queue->first + 1) % vector_size(queue->buffer);
    --queue->count;
    if (queue_empty(queue))
        queue->first = 0;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
