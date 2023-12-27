#include "queue.h"

struct Queue {
    Vector* vector;
    size_t front;
};

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    return queue;
}

void queue_delete(Queue* queue) {
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    vector_push_back(queue->vector, data);
}
Data queue_get(const Queue* queue) {
    if (!queue_empty(queue)) {
        return vector_get(queue->vector, queue->front);
    } else {
        return Data();
    }
}

void queue_remove(Queue* queue) {
    if (!queue_empty(queue)) {
        queue->front = (queue->front + 1) % vector_size(queue->vector);
        vector_resize(queue->vector, vector_size(queue->vector) - 1);
    }
}

bool queue_empty(const Queue* queue) {
    return vector_size(queue->vector) == 0;
}