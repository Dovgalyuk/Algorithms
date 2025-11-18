#include "queue.h"
#include "vector.h"
#include <cstddef>

struct Queue
{
    Vector* vec;
    size_t head;
    size_t tail;
};

Queue *queue_create()
{
    Queue* q = new Queue;
    q->vec = vector_create();
    q->head = 0;
    q->tail = 0;
    return q;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vec);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue->vec->capacity == 0) {
        vector_resize(queue->vec, 1);
    }
    size_t cap = queue->vec->capacity;
    if ((queue->tail + 1) % cap == queue->head) {
        size_t new_cap = cap * 2 + 1;
        Vector* new_vec = vector_create();
        vector_resize(new_vec, new_cap);
        size_t i = 0;
        size_t current = queue->head;
        while (current != queue->tail) {
            vector_set(new_vec, i++, vector_get(queue->vec, current));
            current = (current + 1) % cap;
        }
        queue->head = 0;
        queue->tail = i;
        vector_delete(queue->vec);
        queue->vec = new_vec;
        cap = new_cap;
    }
    vector_set(queue->vec, queue->tail, data);
    queue->tail = (queue->tail + 1) % cap;
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue)) {
        return (Data)0;
    }
    return vector_get(queue->vec, queue->head);
}

void queue_remove(Queue *queue)
{
    if (!queue_empty(queue)) {
        queue->head = (queue->head + 1) % queue->vec->capacity;
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->head == queue->tail;
}
