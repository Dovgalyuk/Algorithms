#include "queue.h"
#include "vector.h"

struct Queue {
    Vector* vector;
    size_t front; // »ндекс начала очереди
    size_t rear; // »ндекс конца очереди

    Queue() {
        vector = vector_create();
        front = 0;
        rear = 0;
    }

    ~Queue() {
        vector_delete(vector);
    }
};

Queue* queue_create() {
    return new Queue;
}

void queue_delete(Queue* queue) {
    delete queue;
}
void queue_insert(Queue* queue, Data data) {
    size_t current_size = vector_size(queue->vector);

    if (current_size == 0) {
        vector_resize(queue->vector, 1);
        vector_set(queue->vector, queue->rear, data);
        queue->rear++;
        return;
    }

    size_t next_rear = (queue->rear + 1) % current_size;

    if (next_rear == queue->front) {
        size_t new_size = current_size * 2;
        Vector* resized_vector = vector_create();
        vector_resize(resized_vector, new_size);

        for (size_t i = queue->front, j = 0; i < current_size; ++i, ++j) {
            vector_set(resized_vector, j, vector_get(queue->vector, i));
        }

        if (queue->front != 0) {
            for (size_t i = 0, j = current_size - queue->front; i < queue->front; ++i, ++j) {
                vector_set(resized_vector, j, vector_get(queue->vector, i));
            }
        }

        vector_delete(queue->vector);
        queue->vector = resized_vector;
        queue->front = 0;
        queue->rear = current_size;
        current_size = new_size;
    }

    vector_set(queue->vector, queue->rear, data);
    queue->rear = (queue->rear + 1) % current_size;
}

Data queue_get(const Queue* queue) {
    if (queue->front == queue->rear) {
        return (Data)0; // ≈сли очередь пуста, возвращаем значение по умолчанию 
    }
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue* queue) {
    if (queue->front == queue->rear) {
        return; // Ќечего удал€ть, если очередь пуста
    }
    queue->front++;

    // ≈сли начало очереди достигло конца вектора, сдвигаем в начало
    if (queue->front == queue->rear) {
        queue->front = 0;
        queue->rear = 0;
    }
}

bool queue_empty(const Queue* queue) {
    return queue->front == queue->rear;
}