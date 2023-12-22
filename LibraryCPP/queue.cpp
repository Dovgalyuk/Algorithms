#include "queue.h"

struct Queue {
    Vector *vector;
};

Queue *queue_create() {
    Queue *queue = new Queue;
    queue->vector = vector_create();  // Using vector_create from vector.cpp
    return queue;
}

void queue_delete(Queue *queue) {
    vector_delete(queue->vector);  // Using vector_delete from vector.cpp
    delete queue;
}

void queue_enqueue(Queue *queue, const std::pair<int, int> &coordinates) {
    vector_resize(queue->vector, vector_size(queue->vector) + 1);  
    vector_set(queue->vector, vector_size(queue->vector) - 1, coordinates);  
}

std::pair<int, int> queue_dequeue(Queue *queue) {
    if (!queue_empty(queue)) {
        std::pair<int, int> frontValue = vector_get(queue->vector, 0); 

        for (size_t i = 1; i < vector_size(queue->vector); ++i) {
            vector_set(queue->vector, i - 1, vector_get(queue->vector, i));
        }

        vector_resize(queue->vector, vector_size(queue->vector) - 1); 

        return frontValue;
    }

    return {-1, -1};  // Modify as needed
}

bool queue_empty(const Queue *queue) {
    return vector_size(queue->vector) == 0;  
}


std::pair<int, int> queue_get(const Queue *queue) {
    if (!queue_empty(queue)) {
        return vector_get(queue->vector, 0);  
    }

    return {-1, -1};
}

void queue_remove(Queue *queue) {
    if (!queue_empty(queue)) {
        for (size_t i = 1; i < vector_size(queue->vector); ++i) {
            vector_set(queue->vector, i - 1, vector_get(queue->vector, i));
        }

        vector_resize(queue->vector, vector_size(queue->vector) - 1); 
    }
}