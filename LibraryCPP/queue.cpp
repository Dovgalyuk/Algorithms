#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t head;
    size_t tail;
    size_t count;
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    vector_resize(queue->vector, 10);
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue* queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    size_t vectorSize = vector_size(queue->vector);
    if (queue->count == vectorSize) {
        size_t newSize = vectorSize * 2;
        vector_resize(queue->vector, newSize);
        if (queue->tail <= queue->head) {
            for (size_t i = 0; i < queue->tail; ++i) {
                vector_set(queue->vector, vectorSize + i, vector_get(queue->vector, i));
            }
            queue->tail = vectorSize + queue->tail;
        }
    }

    vector_set(queue->vector, queue->tail, data);
    queue->tail = (queue->tail + 1) % vector_size(queue->vector);
    queue->count++;
}

Data queue_get(const Queue* queue)
{
    if (queue_empty(queue)) return (Data)0;
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue* queue)
{
    if (!queue_empty(queue)) {
        queue->head = (queue->head + 1) % vector_size(queue->vector);
        queue->count--;
    }
}

bool queue_empty(const Queue* queue)
{
    return queue->count == 0;
}