#include "queue.h"
#include "vector.h"

struct Queue {
    Vector *vector;
    size_t front;
    size_t rear;
    size_t count;
};

Queue *queue_create() {
    Queue *queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue) {
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data) {
    if (queue->count == vector_size(queue->vector)) {
        vector_resize(queue->vector, vector_size(queue->vector) * 2);
    }
    vector_set(queue->vector, queue->rear, data);
    queue->rear = (queue->rear + 1) % vector_size(queue->vector);
    queue->count++;
}

Data queue_get(const Queue *queue) {
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue) {
    if (queue->count > 0) {
        queue->front = (queue->front + 1) % vector_size(queue->vector);
        queue->count--;
    }
}

bool queue_empty(const Queue *queue) {
    return queue->count == 0;
}