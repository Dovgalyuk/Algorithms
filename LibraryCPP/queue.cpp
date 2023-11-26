#include "queue.h"
#include "vector.h"

struct Queue {
    Vector* vector;
    ptrdiff_t front; // Индекс начала очереди
    ptrdiff_t rear; // Индекс конца очереди

    Queue() {
        vector = vector_create();
        vector_resize(vector, 2);
        front = -1;
        rear = -1;
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

void queue_insert(Queue* queue, Data data)
{
    size_t size = vector_size(queue->vector);

    if (queue_empty(queue)) {
        queue->rear = 0;
        queue->front = 0;
    }
    else if (queue->rear % static_cast<int>(size) == queue->front) {
        Vector* buff = vector_create();
        vector_resize(buff, size * 2);

        int counter = 0;

        for (size_t i = queue->front; i < size; i++) {
            vector_set(buff, counter, vector_get(queue->vector, i));
            counter++;
        }
        for (int i = 0; i < queue->rear; i++) {
            vector_set(buff, counter, vector_get(queue->vector, i));
            counter++;
        }
        vector_delete(queue->vector);
        queue->vector = buff;
        queue->front = 0;
        queue->rear = static_cast<int>(size);
        size = vector_size(queue->vector);
    }

    auto rear = queue->rear % size;
    vector_set(queue->vector, rear, data);
    queue->rear = rear + 1;
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