#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t front;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    vector_resize(queue->vector, vector_size(queue->vector) + 1);
    vector_set(queue->vector, vector_size(queue->vector) - 1, data);
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue)
{
    queue->front++;
    if (queue->front >= vector_size(queue->vector)) {
        queue->front = 0;
        vector_resize(queue->vector, 0);
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->front >= vector_size(queue->vector);
}
