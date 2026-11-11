#include "queue.h"
#include "vector.h"

struct Queue {
    Vector* vec;
    size_t head;
    size_t size;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vec = vector_create();
    vector_resize(queue->vec, 8);
    queue->head = 0;
    queue->size = 0;
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
    if (queue->size == cap) {
        size_t new_cap = cap * 2;
        Vector* new_vec = vector_create();
        vector_resize(new_vec, new_cap);
        for (size_t i = 0; i < queue->size; ++i) {
            vector_set(new_vec, i, vector_get(queue->vec, (queue->head + i) % cap));
        }
        vector_delete(queue->vec);
        queue->vec = new_vec;
        queue->head = 0;
        cap = new_cap;
    }
    size_t tail = (queue->head + queue->size) % cap;
    vector_set(queue->vec, tail, data);
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vec, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue->size > 0) {
        size_t cap = vector_size(queue->vec);
        queue->head = (queue->head + 1) % cap;
        queue->size--;
    }
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
