#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* vector;
    size_t head;
    size_t rear;
    size_t size;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->head = 0;
    queue->rear = 0;
    queue->size = 0;
    return queue;
}

void queue_delete(Queue* queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->size == vector_size(queue->vector)) {
        size_t new_size = queue->size == 0 ? 1 : queue->size * 2;
        Vector* new_vector = vector_create();
        vector_resize(new_vector, new_size);

        for (size_t i = 0; i < queue->size; i++) {
            vector_set(new_vector, i, vector_get(queue->vector, ((queue->head + i) % queue->size)));
        }
        vector_delete(queue->vector);
        queue->vector = new_vector;
        queue->head = 0;
        queue->rear = queue->size;
    }

    vector_set(queue->vector, queue->rear, data);
    queue->rear = (queue->rear + 1) % vector_size(queue->vector);
    queue->size++;
}

Data queue_get(const Queue* queue)
{
    if (queue->size == 0) {
        throw std::invalid_argument("Queue is empty");
    }
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue* queue)
{
    if (!queue_empty(queue)) {
        queue->head = (queue->head + 1) % vector_size(queue->vector);
        queue->size--;
    }
}

bool queue_empty(const Queue* queue)
{
    return queue->size == 0;
}
