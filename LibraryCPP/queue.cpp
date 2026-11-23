#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *data;
    size_t first;
    size_t count;
};

Queue *queue_create()
{
    return new Queue{vector_create(), 0, 0};
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data value)
{
    size_t capacity = vector_size(queue->data);

    if (queue->count == capacity)
    {
        size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
        Vector *new_data = vector_create();
        vector_resize(new_data, new_capacity);

        for (size_t i = 0; i < queue->count; ++i)
            vector_set(new_data, i, vector_get(queue->data, (queue->first + i) % capacity));

        vector_delete(queue->data);
        queue->data = new_data;
        queue->first = 0;
        capacity = new_capacity;
    }

    size_t last = (queue->first + queue->count) % capacity;
    vector_set(queue->data, last, value);
    ++queue->count;
}

Data queue_get(const Queue *queue)
{
    if (queue->count == 0)
        return 0;
    return vector_get(queue->data, queue->first);
}

void queue_remove(Queue *queue)
{
    if (queue->count == 0)
        return;

    queue->first = (queue->first + 1) % vector_size(queue->data);
    --queue->count;

    if (queue->count == 0)
        queue->first = 0;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
