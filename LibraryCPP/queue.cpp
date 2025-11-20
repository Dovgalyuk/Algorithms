#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* buffer;
    size_t head;
    size_t tail;
    size_t size;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->buffer = vector_create();
    vector_resize(queue->buffer, 4);
    queue->head = 0;
    queue->tail = 0;
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

    if (queue->size >= vector_size(queue->buffer)) {
        size_t old_capacity = vector_size(queue->buffer);
        size_t new_capacity = old_capacity * 2;
        
        vector_resize(queue->buffer, new_capacity);
        
        if (queue->head > queue->tail) {
            for (size_t i = 0; i < queue->tail; i++) {
                vector_set(queue->buffer, old_capacity + i, vector_get(queue->buffer, i));
                vector_set(queue->buffer, i, 0);
            }
            queue->tail = old_capacity + queue->tail;
        }
    }

    vector_set(queue->buffer, queue->tail, data);
    queue->tail = (queue->tail + 1) % vector_size(queue->buffer);
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
    
    queue->head = (queue->head + 1) % vector_size(queue->buffer);
    queue->size--;

    if (queue->size == 0) {
        queue->head = 0;
        queue->tail = 0;
    }
}

bool queue_empty(const Queue *queue)
{
    return !queue || queue->size == 0;
}
