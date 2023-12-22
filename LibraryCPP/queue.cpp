#include "queue.h"

struct Queue {
    Vector* vector;
};


Queue* queue_create() {
    Queue* queue = new Queue;
    queue->vector = vector_create();
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
    return vector_get(queue->vector, 0);
}

void queue_remove(Queue* queue) {
    if (!queue_empty(queue)) {
        for (size_t i = 1; i < vector_size(queue->vector); ++i) {
            vector_set(queue->vector, i - 1, vector_get(queue->vector, i));
        }
        vector_resize(queue->vector, vector_size(queue->vector) - 1);
    }
}

bool queue_empty(const Queue* queue) {
    return vector_size(queue->vector) == 0;
}