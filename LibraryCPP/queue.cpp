#include "queue.h"
#include "vector.h"
#include <stdexcept> // Добавляем заголовок для std::runtime_error

struct Queue {
    Vector* vector;
    size_t front;
    size_t size;
};

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->vector = vector_create();
    vector_resize(queue->vector, 1);  // Начальный размер
    queue->front = 0;
    queue->size = 0;
    return queue;
}

void queue_delete(Queue* queue) {
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    if (queue->size == vector_size(queue->vector)) {
        size_t new_size = vector_size(queue->vector) * 2 + 1;
        Vector* new_vector = vector_create();
        vector_resize(new_vector, new_size);

        for (size_t i = 0; i < queue->size; i++) {
            vector_set(new_vector, i, vector_get(queue->vector, (queue->front + i) % vector_size(queue->vector)));
        }

        vector_delete(queue->vector);
        queue->vector = new_vector;
        queue->front = 0;
    }
    size_t rear = (queue->front + queue->size) % vector_size(queue->vector);
    vector_set(queue->vector, rear, data);
    queue->size++;
}

Data queue_get(const Queue* queue) {
    if (queue_empty(queue)) {
        throw std::runtime_error("Queue is empty"); // Используем std::runtime_error
    }
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue* queue) {
    if (queue_empty(queue)) {
        throw std::runtime_error("Queue is empty"); // Используем std::runtime_error
    }
    queue->front = (queue->front + 1) % vector_size(queue->vector);
    queue->size--;
}

bool queue_empty(const Queue* queue) {
    return queue->size == 0;
}
