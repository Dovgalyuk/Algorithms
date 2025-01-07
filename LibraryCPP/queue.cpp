#include "vector.h"
#include "queue.h"

struct Queue {
    Vector *vector;
    size_t size;
    size_t front;
    size_t back;
};

Queue *queue_create() {
    Queue *queue = new Queue;
    queue->vector = vector_create();
    queue->size = 0;
    queue->front = 0;
    queue->back = 0;
    return queue;
}

void queue_delete(Queue *queue) {
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    if (queue->size == vector_size(queue->vector)) {
        size_t new_size = queue->size == 0 ? 1 : queue->size * 2; // Увеличиваем размер
        Vector* new_vec = vector_create();
        vector_resize(new_vec, new_size);

        for (size_t i = 0; i < queue->size; ++i) {
            vector_set(new_vec, i, vector_get(queue->vector, (queue->front + i) % vector_size(queue->vector)));
        }
        vector_delete(queue->vector);
        queue->vector = new_vec;
        queue->front = 0;
        queue->back = queue->size;
    }
    vector_set(queue->vector, queue->back, data);
    queue->back = (queue->back + 1) % vector_size(queue->vector);
    queue->size++;
}

Data queue_get(const Queue *queue) {
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue) {
    if (queue->size == 0) return; // Проверка на пустую очередь
    queue->front = (queue->front + 1) % vector_size(queue->vector);
    queue->size--;
}

bool queue_empty(const Queue *queue) {
    return queue->size == 0;
}
