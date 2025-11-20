#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue {
    Vector* buffer = nullptr;
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;
};

Queue* queue_create() {
    Queue* q = new Queue();
    q->buffer = vector_create();
    return q;
}

void queue_delete(Queue* queue) {
    if (queue) {
        vector_delete(queue->buffer);
        delete queue;
    }
}

void queue_insert(Queue* queue, Data data) {
    if (!queue) return;

    Vector* buf = queue->buffer;
    size_t cap = vector_size(buf);

    if (queue->count == cap) {
        size_t new_cap = cap == 0 ? 8 : cap * 2;
        vector_resize(buf, new_cap);

        if (queue->head != 0) {
            for (size_t i = queue->head; i < cap; ++i) {
                Data val = vector_get(buf, i);
                vector_set(buf, i - queue->head, val);
            }
            for (size_t i = 0; i < queue->tail; ++i) {
                Data val = vector_get(buf, i);
                vector_set(buf, i + (cap - queue->head), val);
            }
            queue->head = 0;
            queue->tail = queue->count;
        }
    }

    vector_set(buf, queue->tail, data);
    queue->tail = (queue->tail + 1) % vector_size(buf);
    ++queue->count;
}

Data queue_get(const Queue* queue) {
    if (!queue || queue->count == 0) {
        throw std::out_of_range("queue_get: queue is empty");
    }
    return vector_get(queue->buffer, queue->head);
}

void queue_remove(Queue* queue) {
    if (!queue || queue->count == 0) {
        throw std::out_of_range("queue_remove: queue is empty");
    }
    queue->head = (queue->head + 1) % vector_size(queue->buffer);
    --queue->count;
}

bool queue_empty(const Queue* queue) {
    return !queue || queue->count == 0;
}