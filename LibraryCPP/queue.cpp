#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t head;
    size_t tail;
    size_t count;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    if (queue == nullptr) return;
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue == nullptr || queue->vector == nullptr) return;

    size_t cap = vector_size(queue->vector);

    if (queue->count == cap)
    {
        size_t new_cap = cap == 0 ? 4 : cap * 2;
        Vector* new_vec = vector_create();
        vector_resize(new_vec, new_cap);

        for (size_t i = 0; i < queue->count; ++i)
        {
            size_t old_idx = (queue->head + i) % cap;
            vector_set(new_vec, i, vector_get(queue->vector, old_idx));
        }

        vector_delete(queue->vector);
        queue->vector = new_vec;
        queue->head = 0;
        queue->tail = queue->count;
        cap = new_cap;
    }

    vector_set(queue->vector, queue->tail, data);
    queue->tail = (queue->tail + 1) % cap;
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (queue == nullptr || queue->vector == nullptr || queue->count == 0) return (Data)0;
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue == nullptr || queue->vector == nullptr || queue->count == 0) return;

    size_t cap = vector_size(queue->vector);
    queue->head = (queue->head + 1) % cap;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    if (queue == nullptr || queue->count == 0) return true;
    return false;
}
