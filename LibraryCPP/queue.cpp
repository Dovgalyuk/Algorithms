#include "queue.h"
#include "vector.h"
#include <stdexcept>
#include <cmath>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define RESIZE_FACTOR 1.2

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

void queue_insert(Queue *queue, Data data)
{
    if (!queue) throw std::invalid_argument("The queue pointer is null");

    if ((queue->size + 1) > vector_size(queue->vector))
        vector_resize(queue->vector, max(1, std::ceil(queue->size * RESIZE_FACTOR)));
    
    if ((queue->size + queue->current_index) >= vector_size(queue->vector)){
        for (size_t ind{queue->current_index}; ind < (queue->size + queue->current_index); ++ind)
            vector_set(queue->vector, ind - queue->current_index, vector_get(queue->vector, ind));
        queue->current_index = 0;
    }

    vector_set(queue->vector, queue->current_index + queue->size, data);
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
    queue->size--;
}

bool queue_empty(const Queue *queue)
{
    if (!queue) throw std::invalid_argument("The queue pointer is null");

    return (queue->size == 0);
}
