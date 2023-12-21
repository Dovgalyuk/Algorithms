#include "queue.h"
#include "vector.h"
#include <deque>
#include <iostream>

struct Queue {
    std::deque<Vector> elements;
};

Vector queue_get(const Queue* queue) {
    if (!queue->elements.empty()) {
        return queue->elements.front();
    } else {
        exit(EXIT_FAILURE);
    }
}

void queue_insert(Queue* queue, const Vector& data) {
    queue->elements.push_back(data);
}

void queue_remove(Queue* queue) {
    if (!queue->elements.empty()) {
        queue->elements.pop_front();
    } else {
        exit(EXIT_FAILURE);
    }
}

bool queue_empty(const Queue* queue) {
    return queue->elements.empty();
}