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
    q->head = 0;
    q->count = 0;
    return q;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vec);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t capacity = vector_size(queue->vec);
    
    if (queue->count == capacity)
    {
        size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
        vector_resize(queue->vec, new_capacity);
        
        size_t tail = capacity > 0 ? (queue->head + queue->count) % capacity : 0;
        
        if (tail < queue->head || capacity == 0)
        {
            for (size_t i = 0; i < tail; i++)
            {
                Data val = vector_get(queue->vec, i);
                vector_set(queue->vec, capacity + i, val);
            }
            tail = capacity + tail;
        }
        capacity = new_capacity;
    }
    
    size_t tail = (queue->head + queue->count) % capacity;
    vector_set(queue->vec, tail, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vec, queue->head);
}

void queue_remove(Queue *queue)
{
    queue->head = (queue->head + 1) % vector_size(queue->vec);
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
