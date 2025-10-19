#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    size_t head;
    size_t tail;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue -> vector = vector_create();

    queue -> head = 0;
    queue -> tail = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    if(queue)
    {
        vector_delete(queue -> vector);
        delete queue;
    }
}

size_t queue_size(const Queue *queue)
{
    size_t capacity = vector_capacity(queue -> vector);
    if (queue -> tail >= queue -> head)
    {
        return queue -> tail - queue -> head;
    }
    else
    {
        return capacity - queue -> head + queue -> tail;
    }
}

void queue_expand(Queue *queue)
{
    size_t old_capacity = vector_capacity(queue -> vector);
    size_t new_capacity = old_capacity * 2;
    vector_resize(queue -> vector, new_capacity);

    if (queue -> head > queue -> tail)
    {
        for (size_t i = 0; i < queue -> tail; ++i)
        {
            vector_set(queue -> vector, i + old_capacity, vector_get(queue -> vector, i));  
        }
        queue -> tail += old_capacity;
    }
}

void queue_insert(Queue *queue, Data data)
{
    size_t capacity = vector_capacity(queue->vector);
    size_t size = queue_size(queue);

    if (size == capacity - 1)
    {
        queue_expand(queue);
        capacity = vector_capacity(queue -> vector);
    }

    vector_set(queue -> vector, queue -> tail, data);
    queue -> tail = (queue -> tail + 1) % capacity;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue -> vector, queue -> head);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue))
    {
        return;
    }
    size_t capacity = vector_capacity(queue -> vector);
    queue -> head = (queue -> head + 1) % capacity;
}

bool queue_empty(const Queue *queue)
{
    return queue -> head == queue -> tail;
}
