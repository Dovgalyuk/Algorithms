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
    vector_resize(queue->vector, vector_size(queue->vector) + 1);  
    vector_set(queue->vector, vector_size(queue->vector) - 1, coordinates); 
}

std::pair<int, int> queue_dequeue(Queue *queue) {
    if (vector_size(queue->vector) > 0) {
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
    if (vector_size(queue->vector) > 0) {
        return vector_get(queue->vector, 0);  
    }

    return {-1, -1};  // Modify as needed
}

void queue_remove(Queue *queue) {
    if (vector_size(queue->vector) > 0) {
        // Shift elements to the left to simulate removal
        for (size_t i = 1; i < vector_size(queue->vector); ++i) {
            vector_set(queue->vector, i - 1, vector_get(queue->vector, i));
        }

        vector_resize(queue->vector, vector_size(queue->vector) - 1);  
    }
}

void queue_insert(Queue *queue, size_t index, const std::pair<int, int> &coordinates) {
    if (index <= vector_size(queue->vector)) {
        vector_resize(queue->vector, vector_size(queue->vector) + 1);  
        for (size_t i = vector_size(queue->vector) - 1; i > index; --i) {
            vector_set(queue->vector, i, vector_get(queue->vector, i - 1));
        }

        vector_set(queue->vector, index, coordinates);  // Insert the new element
    }
}