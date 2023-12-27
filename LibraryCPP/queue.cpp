#include "queue.h"

struct Queue {
    Vector* vector;
    size_t front;
    size_t size;
};

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->size = 0;
    return queue;
}

void queue_delete(Queue* queue) {
    if (queue != nullptr) {
        vector_delete(queue->vector);
        delete queue;
    }
}

void queue_insert(Queue* queue, Data data) {
    size_t vectorSize = vector_size(queue->vector);
    vector_resize(queue->vector, vectorSize + 1);
    size_t back = (queue->front + queue->size) % vectorSize;
    vector_set(queue->vector, back, data);
    queue->size++;
}

Data queue_get(const Queue* queue) {
    if (!queue_empty(queue)) {
        return vector_get(queue->vector, queue->front);
    } else {
        return 0;
    }
}

void queue_remove(Queue* queue) {
    if (!queue_empty(queue)) {
        queue->front = (queue->front + 1) % vector_size(queue->vector);
        queue->size--;
        vector_resize(queue->vector, queue->size);
    }
}

bool queue_empty(const Queue* queue) {
    return queue->size == 0;
}