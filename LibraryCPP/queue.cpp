#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    size_t head;
    size_t tail;
    size_t count;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->vector = vector_create();
    vector_resize(queue->vector, 4);
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t size = vector_size(queue->vector);

    if (queue->count == size)
    {
        vector_resize(queue->vector, size * 2);
        if (queue->head > queue->tail)
        {
            queue->tail = queue->tail + size;
        }
    }

    vector_set(queue->vector, queue->tail, data);
    queue->tail++;

    if (queue->tail == vector_size(queue->vector))
    {
        queue->tail = 0;
    }
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue->count == 0)
    {
        return;
    }

    queue->head++;
    
    if (queue->head == vector_size(queue->vector))
    {
        queue->head = 0;
    }

    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
