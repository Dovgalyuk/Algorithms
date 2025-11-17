#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* vector;
    size_t head;   
    size_t count; 
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    vector_resize(queue->vector, 4); 
    queue->head = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    size_t capacity = vector_size(queue->vector);

    if (queue->count >= capacity) {
        size_t old_size = capacity;
        size_t new_size = old_size * 2;

        Vector* new_vector = vector_create();
        vector_resize(new_vector, new_size);

        for (size_t i = 0; i < queue->count; ++i) {
            size_t from_idx = (queue->head + i) % old_size;
            Data val = vector_get(queue->vector, from_idx);
            vector_set(new_vector, i, val);
        }

        vector_delete(queue->vector);
        queue->vector = new_vector;
        queue->head = 0;
    }

    size_t insert_pos = (queue->head + queue->count) % vector_size(queue->vector);
    vector_set(queue->vector, insert_pos, data);
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
