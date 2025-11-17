#include "queue.h"
#include "vector.h"
#include <stdexcept>

struct Queue
{
    Vector* data;
    size_t head;
    size_t count;
};

Queue* queue_create()
{
    Queue* q = new Queue;
    q->data = vector_create();
    q->head = 0;
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
        Vector* new_vector = vector_create();
        vector_resize(new_vector, new_size);

        for (size_t i = 0; i < queue->count; ++i) {
            size_t index = (queue->head + i) % vector_size(queue->data);
            vector_set(new_vector, i, vector_get(queue->data, index));
        }
        vector_delete(queue->data);
        queue->data = new_vector;
        queue->head = 0;
    }
    size_t tail = (queue->head + queue->count) % vector_size(queue->data);
    vector_set(queue->data, tail, data);
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