#include "queue.h"
#include <deque> 
#include "vector.h" 
#include <cstdlib>
struct Queue {
    std::deque<Vector> elements; 
};

Queue *queue_create() {
    Queue *queue = new Queue;
    return queue;
}

void queue_delete(Queue *queue) {
    delete queue;
}

void queue_insert(Queue *queue, const Vector &data) {
    queue->elements.push_back(data);
}

Vector queue_get(const Queue *queue) {
    if (!queue->elements.empty()) {
        return queue->elements.front();
    } else {
        exit(EXIT_FAILURE);
    }
}

void queue_remove(Queue *queue) {
    if (!queue->elements.empty()) {
        queue->elements.pop_front();
    } else {
        exit(EXIT_FAILURE);
    }
}

bool queue_empty(const Queue *queue) {
    return queue->elements.empty();
}