#include "queue.h"
#include "vector.h"
#include <cstddef>

struct Queue
{
    Vector *vector;
    size_t first;
    size_t size;

};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->vector = vector_create();
    queue->first = 0;
    queue->size = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->size == vector_size(queue->vector)) {
        size_t new_capacity;
        if (vector_size(queue->vector) == 0) {
            new_capacity = 1;
        } else {
        new_capacity = vector_size(queue->vector) * 2;
        }
        Vector *new_vector = vector_create();
        vector_resize(new_vector, new_capacity);

        for (size_t i = 0; i < queue->size; i++) {
            size_t index = (queue->first + i) % vector_size(queue->vector);
            vector_set(new_vector, i, vector_get(queue->vector, index));
        }
        Vector *old_vector = queue->vector;
        queue->vector = new_vector;
        queue->first = 0;
        vector_delete(old_vector);
    }
    size_t tail = (queue->first + queue->size) % vector_size(queue->vector);
    vector_set(queue->vector, tail, data);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue)) {
        return (Data)0;
    }
    return vector_get(queue->vector, queue->first);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue)) {
        return;
    }
    queue->first = (queue->first + 1) % vector_size(queue->vector);
    queue->size--;
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
