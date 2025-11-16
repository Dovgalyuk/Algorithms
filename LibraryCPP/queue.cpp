#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* data;
    size_t head;
    size_t tail;
    size_t count;
};

Queue* queue_create()
{
    Queue* q = new Queue;
    q->data = vector_create();
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    vector_resize(q->data, 8);
    return q;
}

void queue_delete(Queue* queue)
{
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->count == vector_size(queue->data)) {
        size_t new_size = vector_size(queue->data) * 2;
        vector_resize(queue->data, new_size);
    }

    vector_set(queue->data, queue->tail, data);
    queue->tail = (queue->tail + 1) % vector_size(queue->data);
    queue->count++;
}

Data queue_get(const Queue* queue)
{
    if (queue->count == 0) {
        throw std::runtime_error("Queue is empty");
    }
    return vector_get(queue->data, queue->head);
}

void queue_remove(Queue* queue)
{
    if (queue->count == 0) {
        throw std::runtime_error("Queue is empty");
    }
    queue->head = (queue->head + 1) % vector_size(queue->data);
    queue->count--;
}

bool queue_empty(const Queue* queue)
{
    return queue->count == 0;
}