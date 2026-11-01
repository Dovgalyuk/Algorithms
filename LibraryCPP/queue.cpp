#include <limits>
#include <memory>
#include <stdexcept>
#include "queue.h"
#include "vector.h"

struct Queue
{
    std::unique_ptr<Vector, decltype(&vector_delete)> buffer{vector_create(), vector_delete};
    size_t first = 0;
    size_t size = 0;
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t capacity = vector_size(queue->buffer.get());
    if (queue->size == capacity)
    {
        const size_t max_size = std::numeric_limits<size_t>::max() / sizeof(Data);
        if (capacity > max_size / 2)
            throw std::length_error("Queue is too large");
        vector_resize(queue->buffer.get(), capacity ? capacity * 2 : 4);
        // In a full wrapped buffer, the prefix follows the old array end.
        // Move that prefix into the new half to preserve the FIFO order.
        for (size_t i = 0; i < queue->first; ++i)
            vector_set(queue->buffer.get(), capacity + i, vector_get(queue->buffer.get(), i));
        capacity = vector_size(queue->buffer.get());
    }
    vector_set(queue->buffer.get(), (queue->first + queue->size) % capacity, data);
    ++queue->size;
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue))
        throw std::out_of_range("Empty queue");
    return vector_get(queue->buffer.get(), queue->first);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue))
        throw std::out_of_range("Empty queue");
    queue->first = (queue->first + 1) % vector_size(queue->buffer.get());
    --queue->size;
    if (queue->size == 0)
        queue->first = 0;
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
