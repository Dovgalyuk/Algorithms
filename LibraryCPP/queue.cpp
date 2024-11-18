#include "queue.h"
#include "vector.h"
#include <cstdlib>

struct Queue {
    Vector* vector;
    Data front;
    Data back;
};

Queue* queue_create() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue != nullptr) {
        queue->vector = vector_create();
        queue->front = queue->back = 0;
    }
    return queue;
}

void queue_delete(Queue* queue) {
    vector_delete(queue->vector);
    free(queue);
}

void queue_insert(Queue* queue, Data data) {
    vector_resize(queue->vector, vector_size(queue->vector) + 1);
    vector_set(queue->vector, queue->back, data);
    queue->back++;
}

Data queue_get(const Queue* queue) {
    if (queue_empty(queue) || queue == nullptr) {
        return (Data)0;
    }
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue* queue) {
    if (!queue_empty(queue)) {
        queue->front++;
    }
}

bool queue_empty(const Queue* queue) {
    if (queue != nullptr && queue->front == queue->back) {
        return true;
    }
    return false;
}
