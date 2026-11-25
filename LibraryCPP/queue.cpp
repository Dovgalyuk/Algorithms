#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue {
    Vector* data;
    size_t size;
    size_t head;
};

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->data = vector_create();
    queue->head = 0;
    queue->size = 0;
    vector_resize(queue->data, 4);
    return queue;
}

void queue_delete(Queue* queue) {
    if (queue == nullptr) return;
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    size_t capacity = vector_size(queue->data);

    if (queue->size == capacity) {
        size_t new_capacity = capacity * 2;
        Vector* new_data = vector_create();
        vector_resize(new_data, new_capacity);

        for (size_t i = 0; i < queue->size; i++) {
            size_t old_index = (queue->head + i) % capacity;
            vector_set(new_data, i, vector_get(queue->data, old_index));
        }

        vector_delete(queue->data);
        queue->data = new_data;
        queue->head = 0;
        capacity = new_capacity;
    }

    size_t tail = (queue->head + queue->size) % capacity;
    vector_set(queue->data, tail, data);
    queue->size++;
}

Data queue_get(const Queue* queue) {
    if (queue_empty(queue)) {
        throw std::out_of_range("queue empty");
    }

    return vector_get(queue->data, queue->head);
}

void queue_remove(Queue* queue) {
    if (queue_empty(queue)) {
        throw std::out_of_range("queue empty");
    }

    queue->head = (queue->head + 1) % vector_size(queue->data);
    queue->size--;
}

bool queue_empty(const Queue* queue) {
    return queue->size == 0;
}