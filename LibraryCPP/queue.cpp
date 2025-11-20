#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* buffer;
    size_t head;
    size_t size;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->buffer = vector_create();
    vector_resize(queue->buffer, 4);
    queue->head = 0;
    queue->size = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    if (!queue) return;
    vector_delete(queue->buffer);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue) return;

    size_t capacity = vector_size(queue->buffer);
    
    if (queue->size >= capacity) {
        size_t new_capacity = capacity * 2;
        
        vector_resize(queue->buffer, new_capacity);
        
        if (queue->head > 0 && queue->head + queue->size > capacity) {
            size_t elements_to_move = capacity - queue->head;
            for (size_t i = 0; i < elements_to_move; i++) {
                size_t old_index = queue->head + i;
                size_t new_index = new_capacity - elements_to_move + i;
                Data value = vector_get(queue->buffer, old_index);
                vector_set(queue->buffer, new_index, value);
                vector_set(queue->buffer, old_index, 0);
            }
            queue->head = new_capacity - elements_to_move;
        }
        
        capacity = new_capacity;
    }

    size_t tail = (queue->head + queue->size) % capacity;
    vector_set(queue->buffer, tail, data);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if (!queue || queue->size == 0) {
        throw std::runtime_error("Queue is empty");
    }
    return vector_get(queue->buffer, queue->head);
}

void queue_remove(Queue *queue)
{
    if (!queue || queue->size == 0) return;

    vector_set(queue->buffer, queue->head, 0);
    
    size_t capacity = vector_size(queue->buffer);
    queue->head = (queue->head + 1) % capacity;
    queue->size--;

    if (queue->size == 0) {
        queue->head = 0;
    }
}

bool queue_empty(const Queue *queue)
{
    return !queue || queue->size == 0;
}
