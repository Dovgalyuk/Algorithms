#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    size_t front;
    size_t back;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->back = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->back == vector_size(queue->vector)) {
        vector_resize(queue->vector, vector_size(queue->vector) + 1);
    }
    vector_set(queue->vector, queue->back, data);
    queue->back++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue)
{
    queue->front++;
    if (queue->front == queue->back) {
        queue->front = 0;
        queue->back = 0;
        vector_resize(queue->vector, 0);
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->front == queue->back;
}
