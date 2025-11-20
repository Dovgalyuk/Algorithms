#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vec;
    size_t head;
    size_t count;
};

Queue *queue_create()
{
    Queue *q = new Queue;
    q->vec = vector_create();
    vector_resize(q->vec, 4);
    q->head = 0;
    q->count = 0;
    return q;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vec);
    delete queue;
}

void queue_expand(Queue *q) {
    size_t old_size = vector_size(q->vec);
    size_t new_size = old_size * 2;
    if (new_size == 0) new_size = 4;

    Vector* new_vec = vector_create();
    vector_resize(new_vec, new_size);

    for (size_t i = 0; i < q->count; ++i) {
        size_t old_index = (q->head + i) % old_size;
        Data val = vector_get(q->vec, old_index);
        
        vector_set(new_vec, i, val);
    }
    vector_delete(q->vec);
    q->vec = new_vec;

    q->head = 0;
}

void queue_insert(Queue *queue, Data data)
{
    size_t cap = vector_size(queue->vec);
    if (queue->count == cap) {
        queue_expand(queue);
        cap = vector_size(queue->vec);
    }

    size_t tail = (queue->head + queue->count) % cap;
    vector_set(queue->vec, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue)) return (Data)0;
    return vector_get(queue->vec, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue)) return;
    
    size_t cap = vector_size(queue->vec);
    queue->head = (queue->head + 1) % cap;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
