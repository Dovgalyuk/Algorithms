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
    size_t currentSize = vector_size(queue->vector);
    if (currentSize == vector_size(queue->vector)) {
        vector_resize(queue->vector, currentSize * 2); 
    }

    size_t back = (queue->front + currentSize) % (currentSize == 0 ? 1 : currentSize);
    vector_set(queue->vector, back, data);
}
Data queue_get(const Queue* queue) {
    return vector_get(queue->vector, queue->front);
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