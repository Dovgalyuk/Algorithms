#include "queue.h"
#include "vector.h"

struct Queue
{
    size_t first;
    size_t last;
    Vector* vector;
    Queue()
    {
        first = 0;
        last = 0;
        vector = vector_create();
    }
    ~Queue()
    {
        vector_delete(vector);
    }
};

Queue* queue_create()
{
    return new Queue;
}

void queue_delete(Queue* queue)
{
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (vector_size(queue->vector) == 0)
        vector_resize(queue->vector, 1);
    if (queue->last + 1 == queue->first) {
        vector_set(queue->vector, queue->last, data);
        queue->last++;
        Vector* Q = vector_create();
        vector_resize(Q, vector_size(queue->vector) + 1);
        int j = 0;
        for (int i = queue->first; i < vector_size(queue->vector); i++, j++) {
            vector_set(Q, j, vector_get(queue->vector, i));
        }
        for (int i = 0; i < queue->last; i++, j++) {
            vector_set(Q, j, vector_get(queue->vector, i));
        }
        vector_delete(queue->vector);
        queue->vector = Q;
        queue->first = 0;
        queue->last = vector_size(queue->vector) - 1;
    }
    else {
        if (queue->last != vector_size(queue->vector) - 1) {
            vector_set(queue->vector, queue->last, data);
            queue->last++;
        }
        else if (queue->first != 0) {
            vector_set(queue->vector, queue->last, data);
            queue->last = 0;
        }
        else {
            vector_set(queue->vector, queue->last, data);
            queue->last++;
            vector_resize(queue->vector, vector_size(queue->vector) + 1);
        }
    }
}

Data queue_get(const Queue* queue)
{
    return vector_get(queue->vector, queue->first);
}

void queue_remove(Queue* queue)
{
    if (queue->first < vector_size(queue->vector) - 1)
        queue->first++;
    else
        if (queue->first != queue->last)
            queue->first = 0;
}

bool queue_empty(const Queue* queue)
{
    return queue->first == queue->last;
}