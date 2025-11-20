#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* buf;
    size_t head;
    size_t tail;
    size_t count;
};

Queue* queue_create()
{
    Queue* q = new Queue;
    q->buf = vector_create();
    vector_resize(q->buf, 4);
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    return q;
}

void queue_delete(Queue* queue) 
{
    vector_delete(queue->buf);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->count == vector_size(queue->buf))
    {
        size_t oldcap = vector_size(queue->buf);
        vector_resize(queue->buf, oldcap * 2);

        for (size_t i = 0; i < queue->count; i++)
        {
            vector_set(queue->buf, i, vector_get(queue->buf, (queue->head + i) % oldcap));
        }
        queue->head = 0;
        queue->tail = queue->count;
    }

    vector_set(queue->buf, queue->tail, data);
    queue->tail = (queue->tail + 1) % vector_size(queue->buf);
    queue->count++;
}

Data queue_get(const Queue* queue) 
{
    return vector_get(queue->buf, queue->head);
}

void queue_remove(Queue* queue)
{
    queue->head = (queue->head + 1) % vector_size(queue->buf);
    queue->count--;
}

bool queue_empty(const Queue* queue) 
{
    return queue->count == 0;
}