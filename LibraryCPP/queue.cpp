#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *buffer;
    size_t head;
    size_t count;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->buffer = vector_create();
    vector_resize(queue->buffer, 1);
    queue->head = 0;
    queue->count = 0;
    return queue;
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
        size_t new_capacity = capacity * 2;

        Vector *new_buffer = vector_create();
        vector_resize(new_buffer, new_capacity);

        for (size_t i = 0; i < queue->count; ++i)
        {
            size_t idx = (queue->head + i) % capacity;
            vector_set(new_buffer, i, vector_get(queue->buffer, idx));
        }

        vector_delete(queue->buffer);
        queue->buffer = new_buffer;
        queue->head = 0;
        capacity = new_capacity;
    }

    size_t tail = (queue->head + queue->count) % capacity;
    vector_set(queue->buffer, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->buffer, queue->head);
}

void queue_remove(Queue *queue)
{
    size_t capacity = vector_size(queue->buffer);
    queue->head = (queue->head + 1) % capacity;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}