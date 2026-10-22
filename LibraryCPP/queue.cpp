#include "queue.h"
#include "vector.h"

static const size_t ind = 4;

struct Queue
{
    Vector *buffer;
    size_t head;
    size_t count;
};

static void queue_grow(Queue *queue)
{
    size_t old_capacity = vector_size(queue->buffer);
    vector_resize(queue->buffer, old_capacity * 2);

    for (size_t i = 0; i < queue->head; i++)
    {
        vector_set(queue->buffer, old_capacity + i, vector_get(queue->buffer, i));
    }
}

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->buffer = vector_create();
    vector_resize(queue->buffer, ind);
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
    if (queue->count == vector_size(queue->buffer))
    {
        queue_grow(queue);
    }

    size_t tail = (queue->head + queue->count) % vector_size(queue->buffer);
    vector_set(queue->buffer, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->buffer, queue->head);
}

void queue_remove(Queue *queue)
{
    queue->head = (queue->head + 1) % vector_size(queue->buffer);
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}