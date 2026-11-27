#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector *data;
    size_t head;
    size_t count;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->data = vector_create();
    queue->head = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    if (queue == nullptr)
        return;

    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue == nullptr)
        throw std::invalid_argument("Null queue");

    size_t capacity = vector_size(queue->data);

    if (queue->count == capacity)
    {
        size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        Vector *new_data = vector_create();

        try
        {
            vector_resize(new_data, new_capacity);

            for (size_t i = 0; i < queue->count; ++i)
            {
                size_t index = (queue->head + i) % capacity;
                vector_set(new_data, i, vector_get(queue->data, index));
            }
        }
        catch (...)
        {
            vector_delete(new_data);
            throw;
        }

        vector_delete(queue->data);
        queue->data = new_data;
        queue->head = 0;
        capacity = new_capacity;
    }

    size_t tail = (queue->head + queue->count) % capacity;

    vector_set(queue->data, tail, data);
    ++queue->count;
}

Data queue_get(const Queue *queue)
{
    if (queue == nullptr || queue->count == 0)
        throw std::out_of_range("Queue is empty");

    return vector_get(queue->data, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue == nullptr || queue->count == 0)
        throw std::out_of_range("Queue is empty");

    size_t capacity = vector_size(queue->data);

    queue->head = (queue->head + 1) % capacity;
    --queue->count;

    if (queue->count == 0)
        queue->head = 0;
}

bool queue_empty(const Queue *queue)
{
    return queue == nullptr || queue->count == 0;
}

