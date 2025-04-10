#include "queue.h"
#include <stdexcept>

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue* queue) {
    if (!queue) return;
    vector_delete(queue->vector);
    delete queue;
}

bool queue_empty(const Queue* queue) {
    return queue->count == 0;
}

void queue_insert(Queue* queue, const Data& data) {
    if (!queue) {
        throw std::runtime_error("Queue is null");
    }

    if (queue->count == queue->vector->capacity) {
        size_t old_capacity = queue->vector->capacity;
        size_t new_capacity = old_capacity * 2;
        Vector* new_vector = vector_create();
        vector_resize(new_vector, new_capacity);

        for (size_t i = 0; i < queue->count; ++i) {
            Data value = vector_get(queue->vector, (queue->front + i) % old_capacity);
            vector_set(new_vector, i, value);
        }

        vector_delete(queue->vector);
        queue->vector = new_vector;
        queue->front = 0;
    }

    size_t insert_index = (queue->front + queue->count) % queue->vector->capacity;
    vector_set(queue->vector, insert_index, data);
    queue->count++;
}

Data queue_get(const Queue* queue) {
    if (queue_empty(queue)) {
        throw std::runtime_error("Attempted to get from empty queue");
    }
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue* queue) {
    if (queue_empty(queue)) {
        throw std::runtime_error("Attempted to remove from empty queue");
    }

    queue->front = (queue->front + 1) % queue->vector->capacity;
    queue->count--;
}