#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    size_t front;
    size_t back;
    size_t size;
    size_t capacity;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->back = 0;
    queue->size = 0;
    queue->capacity = 1;
    vector_resize(queue->vector, queue->capacity);
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->size == queue->capacity) {
        size_t new_capacity = queue->capacity * 2;
        Vector *new_vector = vector_create();
        vector_resize(new_vector, new_capacity);

        for (size_t i = 0; i < queue->size; ++i) {
            vector_set(new_vector, i, vector_get(queue->vector, (queue->front + i) % queue->capacity));
        }

        vector_delete(queue->vector);
        queue->vector = new_vector;
        queue->capacity = new_capacity;
        queue->front = 0;
        queue->back = queue->size;
    }

    vector_set(queue->vector, queue->back, data);
    queue->back = (queue->back + 1) % queue->capacity;
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue)
{
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
