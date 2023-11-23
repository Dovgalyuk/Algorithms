#include "queue.h"
#include "vector.h"

struct Queue {
    Vector* vector;
    size_t front; // Индекс начала очереди
    size_t rear; // Индекс конца очереди

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
    vector_resize(queue->vector, queue->rear + 1); // Увеличиваем размер вектора при вставке элемента
    vector_set(queue->vector, queue->rear, data);
    queue->rear++;
}

Data queue_get(const Queue* queue) {
    if (queue->front == queue->rear) {
        return (Data)0; // Если очередь пуста, возвращаем значение по умолчанию 
    }
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue* queue) {
    if (queue->front == queue->rear) {
        return; // Нечего удалять, если очередь пуста
    }
    queue->front++;

    // Если начало очереди достигло конца вектора, сдвигаем в начало
    if (queue->front == queue->rear) {
        queue->front = 0;
        queue->rear = 0;
    }
}

bool queue_empty(const Queue* queue) {
    return queue->front == queue->rear;
}