#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vec;
    size_t head;
    size_t tail;
    size_t count;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vec = vector_create();
    vector_resize(queue->vec, 8);
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    if (queue) {
        vector_delete(queue->vec);
        delete queue;
    }
}

void queue_insert(Queue *queue, Data data)
{
    size_t cap = vector_size(queue->vec);
    if (queue->count == cap) {
        size_t new_cap = cap * 2;
        Vector* new_vec = vector_create();
        vector_resize(new_vec, new_cap);
        for (size_t i = 0; i < queue->count; ++i) {
            vector_set(new_vec, i, vector_get(queue->vec, (queue->head + i) % cap));
        }
        vector_delete(queue->vec);
        queue->vec = new_vec;
        queue->head = 0;
        queue->tail = queue->count;
        cap = new_cap;
    }
    vector_set(queue->vec, queue->tail, data);
    queue->tail = (queue->tail + 1) % cap;
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vec, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue->count > 0) {
        size_t cap = vector_size(queue->vec);
        queue->head = (queue->head + 1) % cap;
        queue->count--;
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
