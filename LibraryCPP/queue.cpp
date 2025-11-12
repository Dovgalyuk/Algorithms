#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* vector;
    size_t head;  
    size_t tail;  
    size_t count; 
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    vector_resize(queue->vector, 4); 
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->count == vector_size(queue->vector)) {
        size_t old_size = vector_size(queue->vector);
        vector_resize(queue->vector, old_size * 2);

        for (size_t i = 0; i < queue->count; ++i) {
            size_t from_idx = (queue->head + i) % old_size;
            vector_set(queue->vector, i, vector_get(queue->vector, from_idx));
        }

        queue->head = 0;
        queue->tail = queue->count;
    }

    vector_set(queue->vector, queue->tail, data);
    queue->tail = (queue->tail + 1) % vector_size(queue->vector);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue))
        throw std::out_of_range("Queue is empty");
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue))
        throw std::out_of_range("Queue is empty");
    queue->head = (queue->head + 1) % vector_size(queue->vector);
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
