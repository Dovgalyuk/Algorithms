#include "queue.h"
#include <iostream>
#include <stdexcept>

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->back = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue* queue) {
    if (queue == nullptr) return;
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, const Data& data) {
    if (queue == nullptr) {
        exit(1);
    }
    vector_set(queue->vector, queue->back, data);
    queue->back++;
    queue->count++;
}

Data queue_get(const Queue* queue) {
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue* queue) {
    queue->front++;
    queue->count--;
}

bool queue_empty(const Queue* queue) {
    return queue->count == 0;
}
