#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* data;
    size_t head;
    size_t count;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->data = vector_create();
    vector_resize(queue->data, 4);
    queue->head = 0;
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

        for (size_t i = 0; i < queue->count; i++) {
            size_t old_index = (queue->head + i) % old_size;
            Data element = vector_get(queue->data, old_index);
            vector_set(new_vector, i, element);
        }
        vector_delete(queue->data);
        queue->data = new_vector;
        queue->head = 0;
    }

    size_t tail = (queue->head + queue->count) % vector_size(queue->data);
    vector_set(queue->data, tail, data);
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
