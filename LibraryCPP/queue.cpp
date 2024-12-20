#include "queue.h"
#include "vector.h"
#include <iostream>
struct Queue
{
    Vector* vector;
    size_t front;
    size_t back;
    size_t size;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->back = 0;
    queue->size = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->size == vector_size(queue->vector)) {
        Vector* new_vector = vector_create();
        vector_resize(new_vector, queue->size == 0 ? 4 : queue->size * 2);

        for (size_t i = 0; i < queue->size; ++i) {
            vector_set(new_vector, i, vector_get(queue->vector, (queue->front + i) % vector_size(queue->vector)));
        }

        vector_delete(queue->vector);
        queue->vector = new_vector;
        queue->front = 0;
        queue->back = queue->size;
    }
    vector_set(queue->vector, queue->back, data);
    queue->back = (queue->back + 1) % vector_size(queue->vector);
    queue->size++;
}

Data queue_get(const Queue* queue) {
    if (queue_empty(queue)) {
        throw std::out_of_range("Queue is empty");
    }
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue)) {
        throw std::out_of_range("Queue is empty");
    }
    queue->front = (queue->front + 1) % vector_size(queue->vector);
    queue->size--;
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
