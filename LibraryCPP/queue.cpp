#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue { // сапасити убрал.
    Vector* data;
    size_t size;
    size_t head;
};

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->data = vector_create();
    queue->head = 0;
    queue->size = 0;
    vector_resize(queue->data, 12);
    return queue;
}

void queue_delete(Queue* queue) {
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue* queue, Position position) {
    size_t capacity = vector_size(queue->data) / 3;
    if (queue->size == capacity) {
        size_t new_capacity = capacity * 2;
        Vector* new_data = vector_create();
        vector_resize(new_data, new_capacity * 3);
        for (size_t i = 0; i < queue->size; i++) {
            size_t old_index = ((queue->head + i) % capacity) * 3;
            vector_set(new_data, i * 3, vector_get(queue->data, old_index));
            vector_set(new_data, i * 3 + 1, vector_get(queue->data, old_index + 1));
            vector_set(new_data, i * 3 + 2, vector_get(queue->data, old_index + 2));
        }
        vector_delete(queue->data);
        queue->data = new_data;
        queue->head = 0;
        capacity = new_capacity;
    }
    size_t tail = ((queue->head + queue->size) % capacity) * 3;
    vector_set(queue->data, tail, position.x);
    vector_set(queue->data, tail + 1, position.y);
    vector_set(queue->data, tail + 2, position.z);
    queue->size++;
}

Position queue_get(const Queue* queue) {
    if (queue_empty(queue)) throw std::out_of_range("queue empty");
    size_t index = queue->head * 3;
    return {
        static_cast<size_t>(vector_get(queue->data, index)),
        static_cast<size_t>(vector_get(queue->data, index + 1)),
        static_cast<size_t>(vector_get(queue->data, index + 2))
    };
}

void queue_remove(Queue* queue) {
    if (queue_empty(queue)) throw std::out_of_range("queue empty");
    queue->head = (queue->head + 1) % (vector_size(queue->data) / 3);
    queue->size--;
}

bool queue_empty(const Queue* queue) {
    return queue->size == 0;
}