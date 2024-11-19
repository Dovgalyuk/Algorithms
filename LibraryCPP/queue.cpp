#include "queue.h"
#include "vector.h"
#include <stdexcept>
#include <cmath>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#ifndef RESIZE_FACTOR
#define RESIZE_FACTOR 2
#endif

struct Queue
{
    size_t size = 0;
    size_t current_index = 0;
    Vector *vector = vector_create();
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    if (!queue) throw std::invalid_argument("The queue pointer is null");

    vector_delete(queue->vector);
    delete queue;
}

static void queue_order(Queue *queue, size_t old_size)
{
    if (!(queue->current_index)) return;

    size_t bias = vector_size(queue->vector) - old_size;
    for (size_t index{old_size - 1}; index >= queue->current_index; --index)
        vector_set(queue->vector, index + bias, vector_get(queue->vector, index));
    queue->current_index += bias;
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue) throw std::invalid_argument("The queue pointer is null");

    if ((queue->size + 1) > vector_size(queue->vector)){
        size_t old_size = vector_size(queue->vector);
        size_t size2 = std::ceil(queue->size * RESIZE_FACTOR);
        vector_resize(queue->vector, max(1, size2));
        queue_order(queue, old_size);
    }

    vector_set(queue->vector, (queue->current_index + queue->size) % vector_size(queue->vector), data);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if (!queue) throw std::invalid_argument("The queue pointer is null");
    if (queue_empty(queue)) throw std::invalid_argument("The queue is empty");

    return vector_get(queue->vector, queue->current_index);
}

void queue_remove(Queue *queue)
{
    if (!queue) throw std::invalid_argument("The queue pointer is null");
    if (queue_empty(queue)) throw std::invalid_argument("The queue is empty");

    queue->current_index++;
    queue->current_index %= vector_size(queue->vector);
    queue->size--;
}

bool queue_empty(const Queue *queue)
{
    if (!queue) throw std::invalid_argument("The queue pointer is null");

    return (queue->size == 0);
}
