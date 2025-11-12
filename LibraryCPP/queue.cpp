#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* data;
    size_t head;
    size_t tail;
    size_t count;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->data = vector_create();
    vector_resize(queue->data, 4);
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue* queue)
{
    if (queue) {
        vector_delete(queue->data);
        delete queue;
    }
}

void queue_insert(Queue* queue, Data data)
{
    if (!queue) return;
    if (queue->count >= vector_size(queue->data)) {
        size_t old_size = vector_size(queue->data);
        size_t new_size = old_size * 2;

        Vector* new_vector = vector_create();
        vector_resize(new_vector, new_size);
        for (size_t i = 0; i < old_size - queue->head; i++) {
            vector_set(new_vector, i, vector_get(queue->data, queue->head + i));
        }
        for (size_t i = 0; i < queue->tail; i++) {
            vector_set(new_vector, old_size - queue->head + i, vector_get(queue->data, i));
        }
        vector_delete(queue->data);
        queue->data = new_vector;
        queue->head = 0;
        queue->tail = old_size;
    }

    vector_set(queue->data, queue->tail, data);
    queue->tail = (queue->tail + 1) % vector_size(queue->data);
    queue->count++;
}

Data queue_get(const Queue* queue)
{
    if (!queue || queue->count == 0) {
        throw std::runtime_error("Queue is empty");
    }
    return vector_get(queue->data, queue->head);
}

void queue_remove(Queue* queue)
{
    if (!queue || queue->count == 0) {
        throw std::runtime_error("Queue is empty");
    }
    queue->head = (queue->head + 1) % vector_size(queue->data);
    queue->count--;
}
    
bool queue_empty(const Queue* queue)
{
    return !queue || queue->count == 0;
}