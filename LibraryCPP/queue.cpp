#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue {
    Vector* data;
    size_t head;
    size_t count;
    size_t capacity;
};

Queue* queue_create() {
    Queue* q = new Queue;
    q->capacity = 4;
    q->count = 0;
    q->head = 0;
    q->data = vector_create();
    vector_resize(q->data, q->capacity);
    return q;
}

void queue_delete(Queue* q) {
    if (!q) return;
    vector_delete(q->data);
    delete q;
}

void queue_insert(Queue* q, Data value) {
    if (q->count == q->capacity) {
        size_t new_capacity = q->capacity * 2;
        Vector* new_data = vector_create();
        vector_resize(new_data, new_capacity);
        for (size_t i = 0; i < q->count; i++) {
            size_t idx = (q->head + i) % q->capacity;
            vector_set(new_data, i, vector_get(q->data, idx));
        }
        vector_delete(q->data);
        q->data = new_data;
        q->capacity = new_capacity;
        q->head = 0;
    }
    size_t idx = (q->head + q->count) % q->capacity;
    vector_set(q->data, idx, value);
    q->count++;
}

Data queue_get(const Queue* q) {
    if (!q || q->count == 0) throw std::runtime_error("Queue empty");
    return vector_get(q->data, q->head);
}

void queue_remove(Queue* q) {
    if (!q || q->count == 0) throw std::runtime_error("Queue empty");
    q->head = (q->head + 1) % q->capacity;
    q->count--;
}

bool queue_empty(const Queue* q) {
    return !q || q->count == 0;
}
