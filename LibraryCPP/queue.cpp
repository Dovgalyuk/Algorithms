#include "queue.h"
#include "vector.h"

#include <stdexcept>

struct Queue
{
    Vector* storage;
    size_t  head;
    size_t  count;
};

Queue *queue_create()
{
    Queue* q = new Queue;
    q->storage = vector_create();
    q->head = 0;
    q->count = 0;
    return q;
}

void queue_delete(Queue *queue)
{
    if (!queue) return;
    vector_delete(queue->storage);
    delete queue;
}

static void reverse_segment(Queue* queue, size_t lo, size_t hi) {
    while (lo + 1 < hi) {
        Data a = vector_get(queue->storage, lo);
        Data b = vector_get(queue->storage, hi - 1);
        vector_set(queue->storage, lo, b);
        vector_set(queue->storage, hi - 1, a);
        ++lo;
        --hi;
    }
}

static void linearize(Queue* queue) {
    if (queue->head == 0) return;

    size_t n = vector_size(queue->storage);
    size_t h = queue->head;

    reverse_segment(queue, 0, h);
    reverse_segment(queue, h, n);
    reverse_segment(queue, 0, n);

    queue->head = 0;
}

void queue_insert(Queue *queue, Data data)
{
    size_t cap = vector_size(queue->storage);

    if (queue->count == cap) {
        linearize(queue);
        vector_resize(queue->storage, cap ? cap * 2 : 1);
        cap = vector_size(queue->storage);
    }

    size_t tail = (queue->head + queue->count) % cap;
    vector_set(queue->storage, tail, data);
    ++queue->count;
}

bool queue_empty(const Queue* queue)
{
    return queue->count == 0;
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue))
        throw std::out_of_range("queue_get: queue is empty");
    return vector_get(queue->storage, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue))
        throw std::out_of_range("queue_remove: queue is empty");
    queue->head = (queue->head + 1) % vector_size(queue->storage);
    --queue->count;
}
