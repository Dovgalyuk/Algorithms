#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t head;
    size_t tail;
    int kol;
    Queue()
    {
        head = 0;
        tail = 0;
        vector = vector_create();
        vector_resize(vector, 1);
        kol = 0;
    }
};

Queue* queue_create()
{
    return new Queue;
}

void queue_delete(Queue* queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue->tail == vector_size(queue->vector))
    {
        if (queue->head > 0)
            queue->tail = 0;
        else
            vector_resize(queue->vector, vector_size(queue->vector) + 1);

    }
    else if (queue->tail == queue->head)
    {
        vector_resize(queue->vector, vector_size(queue->vector) + queue->head);
        for (int i = 0; i < queue->head; i++)
        {
            queue->tail--;
            vector_set(queue->vector, vector_size(queue->vector) - 1 - i, vector_get(queue->vector, queue->tail));
            vector_set(queue->vector, queue->tail, 0);

        }
    }
    vector_set(queue->vector, queue->tail, data);
    queue->tail++;
    queue->kol++;
}

Data queue_get(const Queue* queue)
{
    if (!queue_empty(queue))
    {
        return vector_get(queue->vector, queue->head);
    }
    else
    {
        return 0;
    }
}

void queue_remove(Queue* queue)
{
    if (!queue_empty(queue))
    {
        if (queue->head >= vector_size(queue->vector) - 1)
        {
            queue->head = 0;
        }
        else
        {
            queue->head++;
        }
    }
}

bool queue_empty(const Queue* queue)
{
    return queue->tail == queue->head;;
}
