#include "queue.h"
#include "vector.h"
#include <cstddef>

struct Queue
{
    Vector* vec;
    size_t head;
    size_t size;
};

Queue *queue_create()
{
    Queue* q = new Queue;
    q->vec = vector_create();
    q->head = 0;
    q->size = 0;
    return q;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vec);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (vector_capacity(queue->vec) == 0) {
        vector_resize(queue->vec, 1);
    }
    size_t cap = vector_capacity(queue->vec);
    if (queue->size == cap) {
        size_t new_cap = cap * 2 + 1;
        Vector* new_vec = vector_create();
        vector_resize(new_vec, new_cap);
        for (size_t i = 0; i < queue->size; ++i) {
            vector_set(new_vec, i, vector_get(queue->vec, (queue->head + i) % cap));
        }
        queue->head = 0;
        vector_delete(queue->vec);
        queue->vec = new_vec;
        cap = new_cap;
    }
    size_t insert_pos = (queue->head + queue->size) % cap;
    vector_set(queue->vec, insert_pos, data);
    queue->size++;
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
        queue->head = (queue->head + 1) % vector_capacity(queue->vec);
        queue->size--;
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
