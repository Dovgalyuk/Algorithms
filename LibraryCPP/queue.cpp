#include "vector.h"
#include "queue.h"
#include <stdexcept>

struct Queue {
    Vector* vector;
    size_t frontIndex;
};

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->frontIndex = 0;
    return queue;
}

void queue_delete(Queue* queue) {
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    vector_resize(queue->vector, vector_size(queue->vector) + 1);
    vector_set(queue->vector, vector_size(queue->vector) - 1, data);
}

Data queue_get(const Queue* queue) {
    if (queue_empty(queue)) {
        throw std::out_of_range("Queue is empty");
    }
    return vector_get(queue->vector, queue->frontIndex);
}

void queue_remove(Queue* queue) {
    if (queue_empty(queue)) {
        throw std::out_of_range("Queue is empty");
    }
    queue->frontIndex++;
    if (queue->frontIndex >= vector_size(queue->vector)) {
        queue->frontIndex = 0;
        vector_resize(queue->vector, 0);  // Очистка вектора
    }
}

bool queue_empty(const Queue* queue) {
    return queue->frontIndex >= vector_size(queue->vector);
}
