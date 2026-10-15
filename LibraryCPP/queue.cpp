#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *buffer;
    size_t head;
    size_t tail;
    size_t count;
    size_t capacity;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->buffer = vector_create();
    queue->capacity = 1;
    vector_resize(queue->buffer, queue->capacity); // size = capacity = 1
    queue->head = 0;
    queue->tail = 0;
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
    if (queue->count == queue->capacity)
    {
        size_t new_capacity = queue->capacity * 2;

        Vector* new_buffer = vector_create();
        vector_resize(new_buffer, new_capacity);

        for (size_t i = 0; i < queue->count; ++i)
        {
            size_t idx = (queue->head + i) % queue->capacity;
            vector_set(new_buffer, i, vector_get(queue->buffer, idx));
        }

        vector_delete(queue->buffer);
        queue->buffer = new_buffer;
        queue->head = 0;
        queue->tail = queue->count;
        queue->capacity = new_capacity;
    }

    vector_set(queue->buffer, queue->tail, data);
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->buffer, queue->head);
}

void queue_remove(Queue *queue)
{
    queue->head = (queue->head + 1) % queue->capacity;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
