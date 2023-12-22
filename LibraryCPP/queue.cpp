#include "queue.h"

struct Queue {
    Vector *vector;
};

Queue *queue_create() {
    Queue *queue = new Queue;
    queue->vector = vector_create();
    return queue;
}

void queue_delete(Queue *queue) {
    vector_delete(queue->vector);
    delete queue;
}

void queue_enqueue(Queue *queue, const std::pair<int, int> &coordinates) {
    vector_push_back(queue->vector, coordinates);
}

std::pair<int, int> queue_dequeue(Queue *queue) {
    if (!queue_empty(queue)) {
        std::pair<int, int> frontValue = vector_get(queue->vector, 0);
        vector_erase(queue->vector, 0);
        return frontValue;
    }

    return {-1, -1};  // Modify as needed
}

bool queue_empty(const Queue *queue) {
    return vector_empty(queue->vector);
}

std::pair<int, int> queue_get(const Queue *queue) {
    if (!queue_empty(queue)) {
        return vector_get(queue->vector, 0);
    }

    return {-1, -1};  // Modify as needed
}

void queue_remove(Queue *queue) {
    if (!queue_empty(queue)) {
        vector_erase(queue->vector, 0);
    }
}